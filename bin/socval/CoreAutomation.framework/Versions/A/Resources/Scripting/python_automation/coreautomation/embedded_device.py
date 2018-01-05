from CoreAutomationFramework import *
from xbs_build import XBSBuild
from uia_app import UIAApp

print "The Python wrapper for CoreAutomation is unmaintained and likely becoming out-of-sync with the actual framework. We strongly recommend that you migrate to using the raw Python/Obj-C bridge. This wrapper may be removed at a later date. More information is at https://eightball.apple.com/luna/index.php/CoreAutomation"

class EmbeddedDevice(object):
    def __init__(self, obj=None):
        if type(obj) == str or type(obj) == unicode:
            self.cam_device = CAMEmbeddedDevice.alloc().initWithUDID_(obj)
        elif type(obj) == CAMEmbeddedDevice:
            self.cam_device = obj
        else:
            raise StandardError("Cannot construct an EmbeddedDevice with '{0}'".format(type(obj)))
    
    @classmethod
    def all_devices(cls):
        devices = list()
        
        internal_devices = CAMEmbeddedDevice.allDevices()
        
        for internal_device in internal_devices:
            devices.append(EmbeddedDevice(internal_device))
        
        return devices
    
    def backup_from_network(self):
        return self.cam_device.backupFromNetwork()

    def backup_from_lockdown(self):
        return self.cam_device.backupFromLockdown()

    def restore_from_network(self, source_identifier=None, copy_backup=False, password=None, wait_for_boot=True):
        return self.cam_device.restoreSourceFromNetwork_copy_password_waitForBoot_(source_identifier, copy_backup, password, wait_for_boot)
    
    def restore_from_lockdown(self, source_identifier=None, copy_backup=False, password=None, wait_for_boot=True):
        return self.cam_device.restoreSourceFromLockdown_copy_password_waitForBoot_(source_identifier, copy_backup, password, wait_for_boot)

    def run_command(self, cmd, wait_for_result=True, as_user='root', with_timeout=3600):
        return self.cam_device.runCommand_andWaitForResult_asUser_withTimeout_(cmd, wait_for_result, as_user, with_timeout)
    
    def send_to_location(self, local_path, remote_path):
        return self.cam_device.send_toLocation_(local_path, remote_path) == 1
    
    def retrieve_to_location(self, remote_path,local_path):
        return self.cam_device.retrieve_toLocation_(remote_path, local_path) == 1
    
    def reboot(self, wait_for_boot=True):
        self.cam_device.reboot_(wait_for_boot)
    
    def jtag_reset(self, wait_for_reappear=True):
        self.cam_device.jtagReset_(wait_for_reappear)
    
    def restore(self, a_build, pr2_doc="CAMEmbeddedDeviceRestoreDefaultErasePRPath", options={}):
        return self.cam_device.restoreBuild_usingRestoreDocument_withOptions_(a_build.cam_build, pr2_doc, options) == 1
    
    def install_app_from_path(self, path):
      self.cam_device.installAppFromPath_(path)
    
    def uninstall_app_with_id(self, bundle_id):
      self.cam_device.uninstallAppWithId_(bundle_id)
    
    def installed_applications(self):
      return self.cam_device.getInstalledApplications()
    
    def app_provisioning_profile(self, path):
        self.cam_device.addProvisioningProfile_(path)
    
    def activate(self):
        self.cam_device.activate()
    
    @property
    def udid(self):
        return self.cam_device.udid()
    
    @property
    def serial_number(self):
        return self.cam_device.serialNumber()
    
    @property
    def location_id(self):
        return self.cam_device.locationID()
    
    @property
    def is_booted(self):
        return self.cam_device.isBooted() == 1
    
    def get_system_date(self):
        return self.cam_device.systemDate()
    
    def set_system_date(self,date):
        self.cam_device.setSystemDate(date)
    
    system_date = property(get_system_date, set_system_date)
    
    @property
    def hardware_model(self):
        return self.cam_device.hardwareModel()
    
    @property
    def hardware_model_prefix(self):
        return self.cam_device.hardwareModelPrefix()
    
    @property
    def product_type(self):
        return self.cam_device.productType()
    
    @property
    def wifi_address(self):
        return self.cam_device.wiFiAddress()
    
    @property
    def build(self):
        return XBSBuild(self.cam_device.build())

    # ui control
    def app_for_name(self, name):
        return UIAApp(self.cam_device.appForName_(name))
    
    def run_scripter(self, js_text, libs=[]):
        return self.cam_device.runScripter_usingLibraryPaths_(js_text, libs)
    
