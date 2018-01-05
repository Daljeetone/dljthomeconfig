use strict;
use warnings;

package UIAApp;

sub new {
    my $class = shift;
    my $obj   = shift;
    
    my $self  = {};
    
    $self->{_cam_uiaapp} = $obj;
    
    bless $self, $class;
    
    return $self;
}

sub uia_app {
    my $self = shift;
    
    return $self->{_cam_uiaapp};
}

sub AUTOLOAD {
    our $AUTOLOAD;
    
    my $self = shift;
    my $method_name = $AUTOLOAD;
    
    $method_name =~ s/.*://;   # strip fully-qualified portion
    
    return if ($method_name eq "DESTROY"); # skip DESTROY, which seems to be called sometimes
    
    #return $self->uia_app()->function_arguments_($method_name, @args)->UTF8String();
    return $self->uia_app()->function_($method_name)->UTF8String();
}

sub interact {
    my $self    = shift;
    my $js_text = shift;
    
    return $self->uia_app()->interact_($js_text)->UTF8String();
}

1;
