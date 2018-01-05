module CAM
    
  class BusBoyUSBController
    attr_accessor :cam_controller
    
    def initialize(obj)
      objc_class = self.class.internal_class_name
      
      case obj
      when String
        @cam_controller = objc_class.alloc.initWithLocationID(obj.hex)
      when Fixnum
        @cam_controller = objc_class.alloc.initWithLocationID(obj)
      when objc_class
        @cam_controller = obj
      else
        raise("Unsure how to create BusBoyUSBController with #{obj.class}")
      end
    end
    
    def self.connect_all()
      internal_class_name.connectAll();
    end
    
    def self.disconnect_all()
      internal_class_name.disconnectAll();
    end
    
    def self.all_controllers()
      controllers = Array.new()
      self.internal_class_name.allControllers().each do |d|
        controllers << self.new(d)
      end
      controllers
    end
    
    def connect()
      @cam_controller.connect()
    end
    
    def disconnect()
      @cam_controller.disconnect()
    end
    
    def location_id()
      @cam_controller.locationID
    end
    
    protected
    def self.internal_class_name
      if using_macruby?
        CAMBusBoyUSBController
      else
        OSX::CAMBusBoyUSBController
      end
    end
    
  end # class BusBoyUSBController
  
end # module CAM
