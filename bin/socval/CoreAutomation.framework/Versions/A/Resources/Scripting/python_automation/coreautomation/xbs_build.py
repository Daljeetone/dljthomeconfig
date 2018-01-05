from CoreAutomationFramework import *

class XBSBuild(object):
    def __init__(self, obj):
        if type(obj) == str:
            self.camBuild = CAMXBSBuild.alloc().initWithString_(obj)
        else:
            self.camBuild = obj
    
    def __str__(self):
        return self.camBuild.description()
        
    def __cmp__(self, other):
        return self.camBuild.compare_(other.camBuild)
    
    @property
    def cam_build(self):
        return self.camBuild
    
    @property
    def build_name(self):
        return self.camBuild.buildName()
    
    @property
    def train_name(self):
        return self.camBuild.train()
    
    @classmethod
    def most_recent_build_for_train(cls,name):
      return CAMXBSBuild.mostRecentBuildForTrain_(name)
