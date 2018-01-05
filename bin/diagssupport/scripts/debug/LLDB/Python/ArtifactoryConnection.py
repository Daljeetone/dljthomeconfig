"""Python API for Artifactory"""

import logging
import os.path
import json
import urllib
import urllib2


# BEGIN COPIED CODE
# Below are inlined OSD.Utilities functions. They are copied out since this
# file needs to be self hosting.
class color:
    PURPLE = '\033[95m'
    CYAN = '\033[96m'
    DARKCYAN = '\033[36m'
    BLUE = '\033[94m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    RED = '\033[91m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
    END = '\033[0m'


def setupLogging(level=logging.DEBUG, name=None):
    log = logging.getLogger(name)
    log.setLevel(level)
    ch = logging.StreamHandler()
    if name:
        formatter = logging.Formatter(color.BOLD + '%(asctime)s<%(levelname)s> ' + name + ' - ' + color.END + ' %(message)s')
    else:
        formatter = logging.Formatter(color.BOLD + '%(asctime)s<%(levelname)s> - ' + color.END + ' %(message)s')
    log.setLevel(level)
    ch.setFormatter(formatter)
    log.handlers = []
    log.propagate = False
    log.addHandler(ch)
    return log


def env_dryrun():
    return "DRYRUN" in os.environ
# END COPIED CODE


class ArtifactoryConnection(object):
    """Represents a connection to Artifactory, an artifact storage service"""

    def __init__(self, artifactory_url, repository, username, api_token, dryrun):
        self.log = setupLogging(logging.INFO)
        self.artifactory_url = artifactory_url
        self.artifactory_repo = repository
        self.dryrun = dryrun or env_dryrun()

        authinfo = urllib2.HTTPPasswordMgrWithDefaultRealm()
        authinfo.add_password(None, artifactory_url, username, api_token)
        urllib2.install_opener(urllib2.build_opener(urllib2.HTTPBasicAuthHandler(authinfo)))

    def urlopen(self, url):
        self.log.info("urlopen: %s", url)
        try:
            r = urllib2.urlopen(url)
        except urllib2.HTTPError as e:
            self.log.info("Request returned %d", e.code())
            raise
        self.log.info('Request returned %s', r.getcode())
        return r

    def search_artifacts(self, properties):
        """Searches Artifactory in the repository named self.artifactory_repo,
        for artifacts matching properties. Returns a dict of URI: file-like object pairs.
        properties cannot contain a property named 'repos'."""

        base_url = reduce(os.path.join, [self.artifactory_url, 'api', 'search', 'prop'])
        properties['repos'] = self.artifactory_repo
        r = self.urlopen(base_url + '?' + urllib.urlencode(properties))
        json_resp = json.loads(r.read())

        downloads = {}
        for result in json_resp['results']:
            result_uri = result['uri']
            uri_resp = self.urlopen(result_uri)

            download_url = json.loads(uri_resp.read())['downloadUri']
            self.log.info('Downloading result')
            file_resp = self.urlopen(download_url)
            downloads[download_url] = file_resp

        return downloads
