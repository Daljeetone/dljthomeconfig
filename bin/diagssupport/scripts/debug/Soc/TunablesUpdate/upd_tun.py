#! /usr/bin/python

import sys,os,re,subprocess
import ConfigParser,json
from radarclient import RadarClient, AuthenticationStrategySPNego, Person, ClientSystemIdentifier

DEBUG = True

class radar:
    def __init__(self):
        self.system_identifier = ClientSystemIdentifier('TunablesUpdater', '1.0')
        self.radar_client = RadarClient(AuthenticationStrategySPNego(), self.system_identifier)
        self.data = {}

    def create(self, title, description, milestone):
        self.data['title'] = title
        self.data['description'] = description
        self.data['component'] = {'name': 'Purple FW Diags', 'version': 'SoC'}
        self.data['classification'] = 'Other Bug'
        self.data['reproducible'] = 'Not Applicable'
        radar = self.radar_client.create_radar(self.data)
        print radar
        print "Successfully created radar: " + str(radar.id)  
        return radar

class Tunables:
    def __init__(self, script='/SWE/Teams/CoreOS/PE/SOC/bin/sdb-tunableh', shasta_path='/Volumes/CaseSensitive/shasta/'):
        self.script = script
        self.shasta = shasta_path
        self.include_dir = 'bootloader/Platform/Apple/Common/Include/'
        self.config = {}
        self.radar = radar()

    def read_config(self,cfg):
        config = ConfigParser.ConfigParser()
        config.read(cfg)
        soc_configs = config.sections()
        self.config["SoCId"] = {}
        self.config["SoC"] = soc_configs
        self.config["Blocks"] = {}
        self.config["files"] = {}
        self.config['target'] = {}
        for soc in soc_configs:
            blocks = json.loads(config.get(soc, 'blocks'))
            self.config["SoCId"][soc] = config.get(soc,'SocId')
            self.config["Blocks"][soc] = blocks
            self.config["files"][soc] = {}
            self.config['target'][soc] = config.get(soc,'BuildTarget')
            for block in blocks:
                self.config['files'][soc][block] = json.loads(config.get(soc,block))
        return True

    def get_shasta_path(self,target):
        path = self.shasta + self.include_dir + target + "/tunables/"
        return path

    def update(self, target):
        print "Update Tunables for " + target
        try:
            filename = "./tunableh_"+target+".out"
            print "Cleaning output directory " + filename
            subprocess.check_output(["rm","-rf",filename])
            print "generating tunables header..."
            print self.script,"-f, -a, -r nightly",target,"-o", filename
            result = subprocess.check_output([self.script,"-f","-a","-r","nightly",target,"-o", filename])
        except subprocess.CalledProcessError as e:
            print e.output
            print "Update failed for ", target
            raise

    def update_module(self, soc, module, rdr=None):
        filename = "./tunableh_" + self.config["SoCId"][soc] + ".out/"
        for f in self.config["files"][soc][module]:
            print "Updating " + f
            subprocess.check_output(["cp",filename+f,self.get_shasta_path(soc)])
        result = subprocess.check_output(["./get_diff"])
        print result
        if result:
            title = module + " tunables update for " + soc
            description = title + '\n\nUpdate headers:\n' + result
            print description
            if rdr == None:
                print "Creating new radar"
                r = self.radar.create(title, description, soc)
                rid = r.id
            else:
                print "Using radar: <rdar://problem/" + str(rdr.id) + "> " + rdr.title
                rid = rdr.id
            branch_name = str(rid)+'-'+module+'-'+soc
            revision_title = "<rdar://problem/" + str(rid) + "> " + title
            self.post4review(branch_name, revision_title, result, self.config['target'][soc], rid)

    def post4review(self, br_name, soc, module, target, rid):        
        try:
            result = subprocess.check_output(["./post4review",br_name, soc, module, target + '.release'])
            print result

            # upload to radar
            print "Uploading to radar:", rid
            rdr = self.radar.radar_client.radar_for_id(rid)
            attachment = rdr.new_attachment(target+'.im4p')
            attachment.set_upload_file(open(self.shasta + 'BuildResults/' + target + '/release/diag/FV/' + target + '.release.im4p', 'rb'))
            rdr.attachments.add(attachment)
            rdr.commit_changes()
        except subprocess.CalledProcessError as e:
            print e.output
            pass

def main(argv):
    # setup environment
    shasta_path = "/Volumes/CaseSensitive/shasta/"
    if os.environ.get('TUNABLES_SHASTA_DIR'):
        shasta_path = os.environ['TUNABLES_SHASTA_DIR']
    if argv and argv[0]:
       shasta_path = argv[0]
    print "shasta dir: ", shasta_path
    os.environ['TUNABLES_SHASTA_DIR'] = shasta_path

    # setup Tunables config
    try:
        t = Tunables(shasta_path = shasta_path)
        t.read_config('tunables.ini')
    except Exception as ex:
        print "Critical Failure"
        print ex
        sys.exit(-1)

    for soc in t.config['SoC']:
        try:
            print "Fetching "+ soc + " tunable headers from seg"
            # Fetch tunables headers for each SoC in config
            t.update(t.config['SoCId'][soc])
            
            for module in t.config['Blocks'][soc]:
                print "Checking " + soc +" "+ module + " Tunables..."
                # Apply tunables if changed
                t.update_module(soc, module)
        except Exception as e:
            print "Failed for ", soc
            print e
            pass

if __name__ == '__main__':
    main(sys.argv[1:])
