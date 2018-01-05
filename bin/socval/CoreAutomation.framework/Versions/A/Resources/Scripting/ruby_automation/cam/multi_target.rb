module CAM
  
  class MultiTarget
    def initialize(devices)
      if using_macruby?
        @cam_multitarget = CAMMultiTarget.new()
      else
        @cam_multitarget = OSX::CAMMultiTarget.new()
      end
      
      @cam_device_hash = Hash.new()
      devices.each do |device|
        @cam_device_hash[device.cam_device] = device
      end
      
      @cam_multitarget.targets = @cam_device_hash.keys
    end
    
    def execute_dispatch(&block)
      group = Dispatch::Group.new()
            
      @cam_device_hash.values.each do |device|
        Dispatch::Queue.concurrent.async(group) do
          block.call(device)
        end
      end
      
      group.wait()
    end
    
    def execute(&block)
      @internal_closure = block
      
      if using_macruby?
        @cam_multitarget.executeSelector(:"simulate_block:", :onObject => self)
      else
        @cam_multitarget.executeSelector_onObject_(:"simulate_block:", self)
      end
    end
    
    def execute_serially(&block)
      @internal_closure = block
      
      if using_macruby?
        @cam_multitarget.executeSelectorSerially(:"simulate_block:", :onObject => self)
      else
        @cam_multitarget.executeSelectorSerially_onObject_(:"simulate_block:", self)
      end
    end
    
    def simulate_block(cam_device)
      internal_device = @cam_device_hash[cam_device]
      @internal_closure.call(internal_device)
    end
    
    # compatibility with Purple::MultiDevice
    def disconnect()
    end
  end
  
end
