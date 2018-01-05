use strict;
use warnings;
use CoreAutomation::XBSBuild;
use CoreAutomation::BridgeExtensions;

print "The Perl wrapper for CoreAutomation is unmaintained and likely becoming out-of-sync with the actual framework. We strongly recommend that you migrate to using the raw Perl/Obj-C bridge. This wrapper may be removed at a later date. More information is at https://eightball.apple.com/luna/index.php/CoreAutomation";

package EmbeddedDevice;

sub new {
    my $class = shift;
    my $obj   = shift;
    
    my $self  = {};
    
    if (ref($obj) eq "CAMEmbeddedDevice") {
        $self->{_cam_device} = $obj;
    }
    elsif (ref($obj) eq "") {
        $self->{_cam_device} = CAMEmbeddedDevice->alloc()->initWithUDID_($obj);
    }
    
    bless $self, $class;
    
    return $self;
}

sub cam_device {
    my $self = shift;
    
    return $self->{_cam_device};
}

sub all_devices {
    my $class = shift;
    my @devices;
    my $device;
    
    my $enumerator = CAMEmbeddedDevice->allDevices()->objectEnumerator();
    
    while ($device = $enumerator->nextObject() and $$device) {
        push @devices, EmbeddedDevice->new($device)
    }
    
    return @devices;
}

sub run_command {
    my ($self, $cmd, $wait, $user, $timeout) = @_;
    
    if (defined $user && defined $timeout) {
        return BridgeExtensions::objc2perl($self->cam_device()->runCommand_andWaitForResult_asUser_withTimeout_($cmd, $wait, $user, $timeout));
    }
    elsif (defined $wait) {
        return BridgeExtensions::objc2perl($self->cam_device()->runCommand_andWaitForResult_($cmd, $wait));
    }
    elsif (defined $cmd) {
        return BridgeExtensions::objc2perl($self->cam_device()->runCommand_($cmd));
    }
    
    die "Unexpected number of arguments to run_command";
}

sub send_to_location {
    my $self = shift;
    my $local_path = shift;
    my $remote_path = shift;
    
    return $self->cam_device()->send_toLocation_($local_path, $remote_path);
}

sub retrieve_to_location {
    my $self = shift;
    my $remote_path = shift;
    my $local_path = shift;
    
    return $self->cam_device()->retrieve_toLocation_($remote_path, $local_path);
}

sub make_root_mount_writable {
    my $self = shift;
    
    $self->cam_device()->makeRootMountWritable();
}

sub disconnect {
    my $self = shift;
    
    $self->cam_device()->disconnect();
}

sub location_id {
    my $self = shift;
    
    return $self->cam_device()->locationID();
}

sub serial_number {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->serialNumber());
}

sub udid {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->udid());
}

use overload q("") => \&to_string;
sub to_string {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->description());
}

sub is_booted {
    my $self = shift;
    
    return $self->cam_device()->isBooted();
}

sub reboot {
    my $self = shift;
    my $wait_for_boot = do { my $arg = shift; defined($arg) ? $arg : 1 };
    
    return $self->cam_device()->reboot_($wait_for_boot);
}

sub jtag_reset {
    my $self = shift;
    my $wait = do { my $arg = shift; defined($arg) ? $arg : 1 };
    
    return $self->cam_device()->jtagReset_($wait);
}

sub hardware_model {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->hardwareModel());
}

sub hardware_model_prefix {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->hardwareModelPrefix());
}

sub product_type {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->productType());
}

sub build {
    my $self = shift;
    my $build;
    
    $build = $self->cam_device()->build();
    
    return XBSBuild->new($build);
}

sub name {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->deviceName());
}

sub set_name {
    my $self = shift;
    my $name = shift;
    
    $self->cam_device()->setDeviceName_($name);
}

sub ram {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->ram());
}

sub disk_capacity {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->diskCapacity());
}

sub battery_id {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->batteryID());
}

sub iboot_version {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->iBootVersion());
}

sub kernel_type {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->kernelType());
}

sub operator_name {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->operatorName());
}

sub boot_args {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->bootArgs());
}

sub core_voltages {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->coreVoltages()->description());
}

sub soc_type {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->socType());
}

sub soc_name {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->socName());
}

sub phone_number {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->phoneNumber());
}

sub cpu_architecture {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->cpuArchitecture());
}

sub baseband_version {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->basebandVersion());
}

sub production_soc {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->productionSOC());
}

sub baseband_serial_number {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->basebandSerialNumber()->description());
}

sub baseband_bootloader {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->basebandBootloaderVersion());
}

sub ecid {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->uniqueChipID());
}

sub die_id {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->dieID());
}

sub imei {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->imei());
}

sub inverse_device_id {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->inverseDeviceID());
}

sub log_path {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->logPath());
}

sub wifi_address {
    my $self = shift;
    
    return BridgeExtensions::objc2perl($self->cam_device()->wiFiAddress());
}

sub activate {
    my $self = shift;
    
    $self->cam_device()->activate();
}

sub is_activated {
    my $self = shift;
    
    return $self->cam_device()->isActivated();
}

# ui control
sub app_for_name {
    my $self     = shift;
    my $app_name = shift;
    my $uiaapp;
    
    $uiaapp = $self->cam_device()->appForName_($app_name);
    
    return UIAApp->new($uiaapp);
}

sub is_in_iboot {
  my $self = shift;

  return $self->cam_device()->isInIBoot;
}

sub time_zone_offset_from_utc {
  my $self = shift;
  
  return BridgeExtensions::objc2perl($self->cam_device()->timeZoneOffsetFromUTC());
}

sub has_gyro {
  my $self = shift;

  return $self->cam_device()->hasGyro;
}

sub soc_revision {
  my $self = shift;
  
  return BridgeExtensions::objc2perl($self->cam_device()->socRevision());
}

sub has_compass {
  my $self = shift;

  return $self->cam_device()->hasCompass;
}

sub unpair {
  my $self = shift;

  return $self->cam_device()->unpair;
}

sub activation_state_acknowledged {
  my $self = shift;

  return ${$self->cam_device()->activationStateAcknowledged};
}

sub time_zone {
  my $self = shift;
  
  return BridgeExtensions::objc2perl($self->cam_device()->timeZone());
}

sub sdio_product_info {
  my $self = shift;

  return BridgeExtensions::objc2perl($self->cam_device()->sdioProductInfo());
}

sub supported_device_families {
  my $self = shift;

  return BridgeExtensions::objc2perl($self->cam_device()->supportedDeviceFamilies());
}

sub region_info {
  my $self = shift;

  return BridgeExtensions::objc2perl($self->cam_device()->regionInfo());
}

sub product_version {
  my $self = shift;

  return BridgeExtensions::objc2perl($self->cam_device()->productVersion());
}

sub password_protected {
  my $self = shift;

  return BridgeExtensions::objc2perl($self->cam_device()->passwordProtected());
}

sub device_color {
  my $self = shift;

  return BridgeExtensions::objc2perl($self->cam_device()->deviceColor());
}

sub bluetooth_address {
  my $self = shift;

  return BridgeExtensions::objc2perl($self->cam_device()->bluetoothAddress());
}

sub sim_status {
  my $self = shift;

  return BridgeExtensions::objc2perl($self->cam_device()->simStatus());
}

sub protocol_version {
  my $self = shift;

  return BridgeExtensions::objc2perl($self->cam_device()->protocolVersion());
}

sub is_in_dfu {
  my $self = shift;

  return $self->cam_device()->isInDFU;
}

sub is_paired {
  my $self = shift;

  return $self->cam_device()->isPaired;
}

sub pair {
  my $self = shift;

  return $self->cam_device()->pair;
}

sub get_to_iboot {
  my $self = shift;

  return $self->cam_device()->getToiBoot;
}

sub activation_state {
  my $self = shift;

  return BridgeExtensions::objc2perl($self->cam_device()->activationState());
}

sub mlb_serial_number {
  my $self = shift;

  return BridgeExtensions::objc2perl($self->cam_device()->mlbSerialNumber());
}

sub partition_type {
  my $self = shift;

  return BridgeExtensions::objc2perl($self->cam_device()->partitionType());
}

sub device_class {
  my $self = shift;

  return BridgeExtensions::objc2perl($self->cam_device()->deviceClass());
}

1;
