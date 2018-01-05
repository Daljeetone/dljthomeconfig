module CAM
  
  class UIAApp
    def initialize(app_object)
      @cam_uia_app = app_object
    end
    
    def method_missing(method, *args, &block)
      if using_macruby?
        @cam_uia_app.function(method.to_s, :arguments => args)
      else
        @cam_uia_app.function_arguments_(method.to_s, args).to_s
      end
    end
    
    def interact(js_text)
      @cam_uia_app.interact(js_text).to_s()
    end
    
  end
  
end
