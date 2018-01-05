module CAM
    
  class EmbeddedDevice
    attr_reader :cam_device # for those that really know what they are doing
    
    def initialize(obj=nil)
      objc_class = self.class.internal_class_name
      
      case obj
      when Hash
        @cam_device = objc_class.alloc.initWithSpecifiers(obj)
      when String
        @cam_device = objc_class.alloc.initWithUDID(obj)
      when NilClass
        @cam_device = objc_class.alloc.init()
      when objc_class
        @cam_device = obj
      else
        raise("Unsure how to create device with #{obj.class}")
      end
    end
    
    def self.all_devices()
      # this is an array coming from objc, so we need to stick it into a 
      # native ruby array to make things transparent
      devices = Array.new()
      self.internal_class_name.allDevices.each do |d|
        devices << self.new(d)
      end
      devices
    end
    def self.first()
      all_devices[0]
    end
    
    def run_command(cmd,wait_for_result=true)
      if using_macruby?
        @cam_device.runCommand(cmd, :andWaitForResult => wait_for_result)
      else
        @cam_device.runCommand_andWaitForResult(cmd, wait_for_result).to_s()
      end
    end

	def build_version()
		@cam_device.buildVersion()
	end

    def send_to_location(local_path,remote_path)
      if using_macruby?
        @cam_device.send(local_path, :toLocation => remote_path)
      else
        @cam_device.send_toLocation(local_path, remote_path)
      end
    end
    
    def retrieve_to_location(remote_path,local_path)
      if using_macruby?
        @cam_device.retrieve(remote_path, :toLocation => local_path)
      else
        @cam_device.retrieve_toLocation(remote_path, local_path)
      end
    end
    
    def make_root_mount_writable()
      @cam_device.makeRootMountWritable()
    end
    
    def disconnect()
      @cam_device.disconnect()
    end

    def pair()
      @cam_device.pair()
    end
    def unpair()
      @cam_device.unpair()
    end
    def get_to_dfu()
      @cam_device.getToDFU()
    end

    def restore(a_build, options={})
      options[:pr2_doc] ||= "CAMEmbeddedDeviceRestoreDefaultErasePRPath"
      
      if using_macruby?
        result = @cam_device.restoreBuild(a_build.cam_build, :usingRestoreDocument => options[:pr2_doc], :withOptions => options)
      else
        result = @cam_device.restoreBuild_usingRestoreDocument_withOptions(a_build.cam_build, options[:pr2_doc], options)
      end
      
      result
    end
    
    # apps and profiles
    def install_app_from_path(path)
      @cam_device.installAppFromPath(path)
    end
    def uninstall_app_with_id(bundle_id)
      @cam_device.uninstallAppWithId(bundle_id)
    end
    def installed_applications()
      @cam_device.getInstalledApplications()
    end
    def add_provisioning_profile(path)
      @cam_device.addProvisioningProfile(path)
    end
    
    # properties
    def udid
      @cam_device.udid.to_s()
    end
    def location_id
      @cam_device.locationID
    end
    def serial_number
      @cam_device.serialNumber.to_s()
    end
    
    # usb control
    def usb_controller=(value)
      @cam_device.setUsbController(value.cam_controller)
    end
    
    def usb_control(options={})
      case options[:type]
      when "BusBoy"
        controller = BusBoyUSBController.new(options[:location_id])
        
        @cam_device.setUsbController(controller.cam_controller)
      else
        raise("The usb controller type '#{}'")
      end
    end
    def connect_usb()
      @cam_device.attachUSBAndWaitForConnect(true)
    end
    def disconnect_usb()
      @cam_device.detachUSBAndWaitForDisconnect(true)
    end
    
    def booted?
      @cam_device.isBooted
    end
    
    def get_to_iboot()
      @cam_device.getToiBoot()
    end
    def get_to_os()
      @cam_device.getToOS()
    end
    
    def reboot(wait_for_boot=true)
      @cam_device.reboot(wait_for_boot)
    end
    def jtag_reset(wait_for_reappear=true)
      @cam_device.jtagReset(wait_for_reappear)
    end
    def system_date
      @cam_device.systemDate
    end
    def system_date=(date)
      @cam_device.systemDate = date
    end
    
    def hardware_model
      @cam_device.hardwareModel.to_s()
    end
    def hardware_model_prefix
      @cam_device.hardwareModelPrefix.to_s()
    end
    def product_type
      @cam_device.productType.to_s()
    end
    def build
      XBSBuild.new(@cam_device.build)
    end
    def password_protected?
      @cam_device.passwordProtected()
    end
    
    def set_default(user,domain,key,value)
      path = "/var/#{user}/Library/Preferences/#{domain}"
      run_command("defaults write '#{path}' '#{key}' '#{value}'")
      run_command("chown mobile:wheel '#{path}.plist'") unless user == 'root'
    end
    
    def name
      @cam_device.deviceName.to_s()
    end
    def name=(new_name)
      @cam_device.setDeviceName(new_name)
    end
    
    def ram
      @cam_device.ram.to_i()
    end
    def disk_capacity
      @cam_device.diskCapacity.to_i()
    end
    def battery_id
      @cam_device.batteryID.to_i()
    end
    def iboot_version
      @cam_device.iBootVersion.to_s()
    end
    def kernel_type
      @cam_device.kernelType.to_s()
    end
    def operator_name
      @cam_device.operatorName.to_s()
    end
    def boot_args
      @cam_device.bootArgs.to_s()
    end
    def core_voltages
      @cam_device.coreVoltages.to_a()
    end
    def soc_type
      @cam_device.socType.to_s()
    end
    def soc_name
      @cam_device.socName.to_s()
    end
    def phone_number
      @cam_device.phoneNumber.to_s()
    end
    def cpu_architecture
      @cam_device.cpuArchitecture.to_s()
    end
    def baseband_version
      @cam_device.basebandVersion.to_s()
    end
    def production_soc?
      if using_macruby?
        @cam_device.productionSOC
      else
        @cam_device.productionSOC.boolValue()
      end
    end
    def baseband_serial_number
      @cam_device.basebandSerialNumber.to_s()
    end
    def baseband_bootloader
      @cam_device.basebandBootloaderVersion.to_s()
    end
    def ecid
      @cam_device.ecid.to_s()
    end
    def die_id
      @cam_device.dieID.to_s()
    end
    def imei
      @cam_device.imei.to_s()
    end
    def inverse_device_id
      @cam_device.inverseDeviceID.to_s()
    end
    def log_path
      @cam_device.logPath.to_s()
    end
    def wifi_address
      @cam_device.wiFiAddress.to_s()
    end
    
    def activate()
      @cam_device.activate()
    end
    def activated?
      @cam_device.isActivated
    end
    
    def responsive?
      @cam_device.isResponsive
    end
    
    # ui control
    def app_for_name(name)
      UIAApp.new(@cam_device.appForName(name))
    end
    def run_scripter(js_text, libs=[])
      if using_macruby?
        @cam_device.runScripter(js_text, :usingLibraryPaths => libs)
      else
        @cam_device.runScripter_usingLibraryPaths_(js_text, libs).to_s()
      end
    end

    # compatibility with Purple::Device
    alias :issue_cmd                :run_command
    alias :send_file                :send_to_location
    alias :retrieve_file            :retrieve_to_location
    alias :reboot_and_wait_for_boot :reboot
    alias :make_fs_writable         :make_root_mount_writable
    
    alias :ram_size                 :ram
    alias :full_hardware_model      :hardware_model
    
    def issue_async_cmd(cmd)
      run_command(cmd, false)
    end
    
    def profile
      hash = Hash.new
      
      hash['ECID']            = ecid
      hash['Device Name']     = name
      hash['Hardware Model']  = hardware_model
      hash['UDID']            = udid
      hash['Build']           = build.to_s
      hash['iBoot']           = iboot_version
      hash['Baseband']        = baseband_version
      hash['Operator']        = operator_name
      hash['Kernel']          = kernel_type
      hash['boot-args']       = boot_args
      hash['Core Voltages']   = core_voltages.join(" ")
      # hash['LCD Panel ID']    = lcd_panel_id
      # hash['Raw Panel ID']    = raw_panel_id
      # if(raw_panel_id.length > 0)
      #   panel = Hash.new
      #   panel['Build']                 = lcm_build
      #   panel['Vendor']                = lcm_vendor
      #   panel['Device']                = lcm_device
      #   panel['Autoboot Support']      = lcm_autoboot
      #   panel['Native Color']          = lcm_native_color
      #   panel['Backlight Calibration'] = lcm_backlight_calib
      #   hash['LCM'] = panel
      # end
      hash['Serial Number']     = serial_number
      hash['Die-ID']            = die_id
      hash["Battery ID"]        = battery_id
      hash["IMEI"]              = imei
      # hash["iBoot Type"]        = iboot_type
      hash["SoC"]               = soc_name
      hash["Inverse Device ID"] = inverse_device_id
      hash["Disk Capacity"]     = disk_capacity
      hash["Production SOC"]    = production_soc?
      hash["RAM Size"]          = ram
      hash["Baseband Serial Number"] = baseband_serial_number
      
      hash
    end
    
    protected
    def self.internal_class_name
      if using_macruby?
        CAMEmbeddedDevice
      else
        OSX::CAMEmbeddedDevice
      end
    end
  end
  
end
