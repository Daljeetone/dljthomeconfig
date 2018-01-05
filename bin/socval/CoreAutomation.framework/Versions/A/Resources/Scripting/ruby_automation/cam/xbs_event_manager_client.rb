module CAM
    
  class XBSEventManagerClient
    
    def initialize()
    end
    
    def self.wait_for_next_build(trains,images)
      train_set = nsset_with_array(trains)
      image_set = nsset_with_array(images)
      
      if using_macruby?
        build = internal_class_name.waitForNextBuildInTrains(train_set, :containingImages => image_set)
      else
        build = internal_class_name.waitForNextBuildInTrains_containingImages_(train_set, image_set)
      end
      
      XBSBuild.new(build)
    end
    
    protected
    def self.internal_class_name
      if using_macruby?
        CAMXBSEventManagerClient
      else
        OSX::CAMXBSEventManagerClient
      end
    end
    
    def self.nsset_with_array(array)
      set = nil
      
      if using_macruby?
        set = NSMutableSet.new
        
        array.each { |obj| set.addObject(obj) }
      else
        set = OSX::NSMutableSet.new
        
        array.each { |obj| set.addObject_(obj) }
      end
      
      set
    end
    
  end # class XBSEventManagerClient
  
end # module CAM
