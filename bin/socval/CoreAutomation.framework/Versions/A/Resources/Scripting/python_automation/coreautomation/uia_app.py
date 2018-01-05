from CoreAutomationFramework import *

class UIAApp(object):
    def __init__(self, obj=None):
        self.cam_uia_app = obj
    
    def interact(self, js_text):
        return self.cam_uia_app.interact_(js_text)
        
    def __getattr__(self, name):
        def call_wrapper(*args):
            return self.cam_uia_app.function_arguments_(name, args)
        
        return call_wrapper
