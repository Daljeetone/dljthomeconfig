module CAM
  
  class XBSBuild
    include Comparable
    
    attr_reader :cam_build
    
    def initialize(obj)
      case obj
      when String
        @cam_build = self.class.internal_class_name.alloc.initWithString(obj)
      else
        @cam_build = obj
      end
    end
    
    def build_name
      @cam_build.buildName.to_s()
    end
    
    def train_name
      @cam_build.train.to_s()
    end
    
    def to_s()
      name
    end
    
    def <=>(other)
      @cam_build.compare(other.cam_build)
    end
    
    def name
      @cam_build.description.to_s()
    end
    
    def self.most_recent_build_for_train(name)
      self.new(self.internal_class_name.mostRecentBuildForTrain(name))
    end
    
    protected
    def self.internal_class_name
      if using_macruby?
        CAMXBSBuild
      else
        OSX::CAMXBSBuild
      end
    end
  end
  
end
