use strict;
use warnings;

package XBSBuild;

sub new {
    my $class = shift;
    my $obj   = shift;
    
    my $self  = {};
    
    if (ref($obj) eq "CAMXBSBuild") {
        $self->{_cam_build} = $obj;
    }
    else {
        $self->{_cam_build} = CAMXBSBuild->alloc()->initWithString_($obj);
    }
    
    bless $self, $class;
    
    return $self;
}

sub cam_build {
    my $self = shift;
    
    return $self->{_cam_build};
}

sub build_name {
    my $self = shift;
    
    return $self->cam_build()->buildName()->UTF8String();
}

sub train_name {
    my $self = shift;
    
    return $self->cam_build()->train()->UTF8String();
}

use overload q("") => \&to_string;
sub to_string {
    my $self = shift;
    
    return $self->cam_build()->description()->UTF8String();
}

sub compare {
    my $self  = shift;
    my $other = shift;
    
    return $self->cam_build()->compare_($other->cam_build());
}

use overload "==" => \&is_equal;
use overload "eq" => \&is_equal;
sub is_equal {
    my $self  = shift;
    my $other = shift;
    
    return $self->compare($other) == 0;
}

use overload ">" => \&is_greater_than;
use overload "gt" => \&is_greater_than;
sub is_greater_than {
    my $self  = shift;
    my $other = shift;
    
    return $self->compare($other) == 1;
}

use overload ">=" => \&is_greater_than_or_equal_to;
use overload "ge" => \&is_greater_than_or_equal_to;
sub is_greater_than_or_equal_to {
    my $self  = shift;
    my $other = shift;
    
    return $self->is_greater_than($other) or $self->is_equal($other);
}

use overload "<" => \&is_less_than;
use overload "lt" => \&is_less_than;
sub is_less_than {
    my $self  = shift;
    my $other = shift;
    
    return $self->compare($other) == -1;
}

use overload "<=" => \&is_greater_than_or_equal_to;
use overload "le" => \&is_greater_than_or_equal_to;
sub is_less_than_or_equal_to {
    my $self  = shift;
    my $other = shift;
    
    return $self->is_less_than($other) or $self->is_equal($other);
}

1;
