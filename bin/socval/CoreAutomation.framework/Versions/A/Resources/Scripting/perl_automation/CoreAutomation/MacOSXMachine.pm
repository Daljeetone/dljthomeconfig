use strict;
use warnings;
use CoreAutomation::XBSBuild;

package MacOSXMachine;

sub new {
    my $class = shift;
    my $obj   = shift;
    
    my $self  = {};
    
    $self->{_cam_machine} = $obj;
    
    bless $self, $class;
    
    return $self;
}

sub local_machine {
    my $class = shift;

    return MacOSXMachine->new(CAMEmbeddedDevice->localMachine())
}

sub cam_machine {
    my $self = shift;
    
    return $self->{_cam_machine};
}

sub build {
    my $self = shift;
    my $build;
    
    $build = $self->cam_machine()->build();
    
    return XBSBuild->new($build);
}

sub hostname {
    my $self = shift;
    
    return $self->cam_machine()->hostname()->UTF8String();
}

sub sdk_version {
    my $self = shift;
    my $sdk  = shift;
    
    my $version = `xcodebuild -sdk $sdk -version ProductBuildVersion`;
    
    $version =~ s/\s+$//; #remove trailing spaces
    
    return $version;
}

sub ios_sdk_version {
    my $self = shift;
    
    return $self->sdk_version("iphoneos.internal");
}

1;
