module CAM
  
  class WiFiInterface
    def initialize(obj)
      @cam_wifi = obj
    end
    
    def power=(value)
      @cam_wifi.setPower(value)
    end
    
    def power
      @cam_wifi.power == 1
    end
    
    def disassociate()
      @cam_wifi.disassociate()
    end
    
    def join_network(ssid, password=nil, preferred=true)
      if using_macruby?
        @cam_wifi.joinFirstNetworkMatching(ssid, :withPassword => password, :makePreferred => preferred)
      else
        @cam_wifi.joinFirstNetworkMatching_withPassword_(ssid, password, preferred)
      end
    end
    
    def remove_all_preferred_networks()
      @cam_wifi.removeAllPreferredNetworks()
    end
  end # class WiFiInterface
  
end
