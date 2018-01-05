module CAM
  
  class MacOSXMachine
    def initialize(obj=nil)
      objc_class = self.class.internal_class_name
      
      case obj
      when String
        @cam_machine = objc_class.alloc.init()
        self.address = obj
      when NilClass
        @cam_machine = objc_class.alloc.init()
      when objc_class
        @cam_machine = obj
      else
        raise("Unsure how to create MacOSXMachine with #{obj.class}")
      end
    end
    
    def self.local_machine()
      self.new(self.internal_class_name.localMachine())
    end
    
    def username=(value)
      @cam_machine.setUsername(value)
    end
    
    def username
      @cam_machine.username.to_s()
    end
    
    def password=(value)
      @cam_machine.setPassword(value)
    end
    
    def password
      @cam_machine.password.to_s()
    end
    
    def address=(value)
      @cam_machine.setTargetAddress(value)
    end
    
    def address
      @cam_machine.targetAddress().to_s()
    end
    
    def connect()
      @cam_machine.connect()
    end
    
    def disconnect()
      @cam_machine.disconnect()
    end
    
    def mount_url(url)
      url = self.class.url_class_name.URLWithString(url)
      
      if using_macruby?
        @cam_machine.mountURL(url, :error => nil)
      else
        @cam_machine.mountURL_error_(url, nil)
      end
    end
    
    def unmount_url(url)
      url = self.class.url_class_name.URLWithString(url)
      
      if using_macruby?
        @cam_machine.unmountURL(url, :error => nil)
      else
        @cam_machine.unmountURL_error_(url, nil)
      end
    end
    
    def run_command(cmd, wait_for_result=true)
      if using_macruby?
        @cam_machine.runCommand(cmd, :andWaitForResult => wait_for_result)
      else
        @cam_machine.runCommand_andWaitForResult(cmd, wait_for_result).to_s()
      end
    end
    
    def send_to_location(local_path, remote_path)
      if using_macruby?
        @cam_machine.send(local_path, :toLocation => remote_path)
      else
        @cam_machine.send_toLocation(local_path, remote_path)
      end
    end
    
    def retrieve_to_location(remote_path, local_path)
      if using_macruby?
        @cam_machine.retrieve(remote_path, :toLocation => local_path)
      else
        @cam_machine.retrieve_toLocation(remote_path, local_path)
      end
    end
    
    def hostname
      @cam_machine.hostname.to_s
    end
    
    def sdk_version(sdk_type)
      `xcodebuild -sdk #{sdk_type} -version ProductBuildVersion`.strip()
    end
    
    def ios_sdk_version
      sdk_version("iphoneos.internal")
    end
    
    protected
    attr_reader :cam_machine
    
    def self.internal_class_name
      if using_macruby?
        CAMMacOSXTarget
      else
        OSX::CAMMacOSXTarget
      end
    end
    
    def self.url_class_name
      if using_macruby?
        NSURL
      else
        OSX::NSURL
      end
    end
  end
  
end
