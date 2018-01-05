use strict;
use warnings;

package BridgeExtensions;

# if the perl-objc bridge worked as you'd expect, this would not be necessary
sub objc2perl {
    my $obj = shift;
    
    # checking class names here is incredibly fragile
    if (ref($obj) eq 'NSCFString') {
        return $obj->UTF8String();
    }
    elsif (ref($obj) eq 'NSCFBoolean') {
        return $obj->boolValue();
    }
    elsif (ref($obj) eq 'NSCFNumber') {
        return $obj->stringValue()->UTF8String()
    }
    elsif (ref($obj) eq 'NSCFArray') {
        my @perl_array;
        my $sub_obj;
        
        my $enumerator = $obj->objectEnumerator();
        
        while ($sub_obj = $enumerator->nextObject() and $$sub_obj) {
            push @perl_array, convert_from_objc_to_perl($sub_obj);
        }
        
        return @perl_array;
    }
    elsif (ref($obj) eq 'CAMEmbeddedDevice') {
        return EmbeddedDevice->new($obj);
    }
    return $obj;
}

1;
