#!/usr/bin/python

import lldb

class value(object):
    '''A class that wraps an lldb.SBValue object and returns an object that
    can be used as an object with attribytes:\n
    argv = a.value(lldb.frame.FindVariable('argv'))\n
    argv.name - return the name of the value that this object contains\n
    argv.type - return the lldb.SBType for this value
    argv.type_name - return the name of the type
    argv.size - return the byte size of this value
    argv.is_in_scope - return true if this value is currently in scope
    argv.is_pointer - return true if this value is a pointer
    argv.format - return the current format for this value
    argv.value - return the value's value as a string
    argv.summary - return a summary of this value's value
    argv.description - return the runtime description for this value
    argv.location - return a string that represents the values location (address, register, etc)
    argv.target - return the lldb.SBTarget for this value
    argv.process - return the lldb.SBProcess for this value
    argv.thread - return the lldb.SBThread for this value
    argv.frame - return the lldb.SBFrame for this value
    argv.num_children - return the number of children this value has
    argv.children - return a list of sbvalue objects that represents all of the children of this value
    '''
    def __init__(self, sbvalue):
        self.sbvalue = sbvalue

    def __nonzero__(self):
        return self.sbvalue.__nonzero__()

    def __repr__(self):
        return self.sbvalue.__repr__()

    def __str__(self):
        return self.sbvalue.__str__()

    def __getitem__(self, key):
        if type(key) is int:
            return value(self.sbvalue.GetChildAtIndex(key, lldb.eNoDynamicValues, True))
        raise TypeError
    
    def __getattr__(self, name):
        if name == 'name':
            return self.sbvalue.GetName()
        if name == 'type':
            return self.sbvalue.GetType()
        if name == 'type_name':
            return self.sbvalue.GetTypeName()
        if name == 'size':
            return self.sbvalue.GetByteSize()
        if name == 'is_in_scope':
            return self.sbvalue.IsInScope()
        if name == 'is_pointer':
            return self.sbvalue.TypeIsPointerType()
        if name == 'format':
            return self.sbvalue.GetFormat ()
        if name == 'value':
            return self.sbvalue.GetValue ()
        if name == 'summary':
            return self.sbvalue.GetSummary ()
        if name == 'description':
            return self.sbvalue.GetObjectDescription ()
        if name == 'location':
            return self.sbvalue.GetLocation ()
        if name == 'target':
            return self.sbvalue.GetTarget()
        if name == 'process':
            return self.sbvalue.GetProcess()
        if name == 'thread':
            return self.sbvalue.GetThread()
        if name == 'frame':
            return self.sbvalue.GetFrame()
        if name == 'num_children':
            return self.sbvalue.GetNumChildren()
        if name == 'children':
            # Returns an array of sbvalue objects, one for each child of 
            # the value for the lldb.SBValue
            children = []
            for i in range (self.sbvalue.GetNumChildren()):
                children.append(value(self.sbvalue.GetChildAtIndex(i, lldb.eNoDynamicValues, True)))
            return children
        raise AttributeError



class variable_type(object):
    '''Worker class for variable class'''
    def __init__(self, var):
        self.sbvalue = var.sbvalue
        self.sbtype  = var.sbtype

    def __str__(self):
        return self.sbvalue.__str__()

    def __nonzero__(self):
        return self.sbvalue.__nonzero__()

    def __repr__(self):
        return self.sbvalue.__repr__()

    def __str__(self):
        return self.sbvalue.__str__()

    @property
    def name(self):
        return self.sbvalue.GetName()

    @property
    def type(self):
        return self.sbvalue.GetType()

    @property
    def type_name(self):
        return self.sbvalue.GetTypeName()

    @property
    def size(self):
        return self.sbvalue.GetByteSize()

    @property
    def is_in_scope(self):
        return self.sbvalue.IsInScope()

    @property
    def is_pointer(self):
        return self.sbvalue.TypeIsPointerType()

    @property
    def format(self):
        return self.sbvalue.GetFormat ()

    @property
    def value(self):
        return self.sbvalue.GetValue ()

    @property
    def summary(self):
        return self.sbvalue.GetSummary ()

    @property
    def description(self):
        return self.sbvalue.GetObjectDescription ()

    @property
    def location(self):
        return self.sbvalue.GetLocation ()

    @property
    def target(self):
        return self.sbvalue.GetTarget()

    @property
    def process(self):
        return self.sbvalue.GetProcess()

    @property
    def thread(self):
        return self.sbvalue.GetThread()

    @property
    def frame(self):
        return self.sbvalue.GetFrame()

    @property
    def num_children(self):
        return self.sbvalue.GetNumChildren()

    @property
    def children(self):
        # Returns an array of sbvalue objects, one for each child of 
        # the value for the lldb.SBValue
        children = []
        for i in range (self.sbvalue.GetNumChildren()):
            children.append(value(self.sbvalue.GetChildAtIndex(i, lldb.eNoDynamicValues, True)))
        return children

    def sizeof(self):
        return self.sbvalue.size

    def addressof(self):
        return self.sbvalue.address_of.unsigned

    def typeof(self):
        return self.sbvalue.GetTypeName()

    def offsetof(self, TypeName=""):
        if TypeName == "":
            TypeName = "%s" % self.sbtype.name.rstrip('*').rstrip(' ')
        sbtype = lldb.target.FindFirstType (TypeName)
        if sbtype is not None:
            for sbtype_member in sbtype.fields:
                if sbtype_member.name == self.sbvalue.GetName():
                    return sbtype_member.byte_offset
        raise TypeError
    
    
class variable(object):
    '''A class that treats a lldb.SBValue and allows it to be used just as
    a variable would be in code. So if you have a Point structure variable 
    in your code, you would be able to do: "pt.x + pt.y"
    pt = variable("frame variable or global name")
    pt = variable (0x12340000, "struct pt")
    pt = variable (lldb.SBType, "struct pt")
    pt = variable (lldb.SBType)
    The .struct. member provides the convenience methods:
    pt.struct.name - return the name of the value that this object contains\n
    pt.struct.type - return the lldb.SBType for this value
    pt.struct.type_name - return the name of the type
    pt.struct.size - return the byte size of this value
    pt.struct.is_in_scope - return true if this value is currently in scope
    pt.struct.is_pointer - return true if this value is a pointer
    pt.struct.format - return the current format for this value
    pt.struct.value - return the value's value as a string
    pt.struct.summary - return a summary of this value's value
    pt.struct.description - return the runtime description for this value
    pt.struct.location - return a string that represents the values location (address, register, etc)
    pt.struct.target - return the lldb.SBTarget for this value
    pt.struct.process - return the lldb.SBProcess for this value
    pt.struct.thread - return the lldb.SBThread for this value
    pt.struct.frame - return the lldb.SBFrame for this value
    pt.struct.num_children - return the number of children this value has
    pt.struct.children - return a list of sbvalue objects that represents all of the children of this value
    pt.struct.sizeof - size of structure or variable
    pt.struct.addressof - address of structure or variable
    pt.struct.typeof - type of structure or variable as a string
    pt.struct.offsetof - offset of member in structure
    '''
    def __init__(self, sbvalue, ctype=None, sbtype=None):
        ''' duck typed init: variable, address +  type, SBType, or SBType
        with a cast:
          variable ("frame variable or global name")
          variable (0x12340000, "struct pt")
          variable (lldb.SBType, "struct pt")
          variable (lldb.SBType)
        '''
        self.sbtype = sbtype
        self.sbvalue = None
        if isinstance (sbvalue, basestring):
            for Frame in lldb.thread.frames:
                var = Frame.FindVariable(sbvalue)
                if var:
                    self.sbvalue = var
                    break
            if self.sbvalue is None:
                global_var = lldb.target.FindGlobalVariables (sbvalue, 0).GetValueAtIndex(0)
                if global_var:
                    self.sbvalue = global_var

        elif (isinstance (sbvalue, int) or isinstance (sbvalue, long))  and isinstance (ctype, basestring):
            address = lldb.frame.EvaluateExpression("0x%x" % sbvalue)
            if address:
                sbtype = lldb.target.FindFirstType(ctype)
                if sbtype:
                    self.sbvalue = address.CreateValueFromAddress (ctype, sbvalue, sbtype)
        elif isinstance (ctype, basestring):
            sbtype = lldb.target.FindFirstType(ctype)
            if sbtype:
                self.sbvalue = sbvalue.CreateValueFromAddress (ctype, sbvalue, sbtype)
        else:
            self.sbvalue = sbvalue

        if self.sbvalue is None:
            raise TypeError

    def __nonzero__(self):
        return self.sbvalue.__nonzero__()

    def __repr__(self):
        return self.sbvalue.__repr__()

    def __str__(self):
        return self.sbvalue.__str__()

    def __getitem__(self, key):
        # Allow array access if this value has children...
        if isinstance(key, int):
            return variable(self.sbvalue.GetValueForExpressionPath("[%i]" % key))
        raise TypeError

    def __getattr__(self, name):
        child_sbvalue = self.sbvalue.GetChildMemberWithName (name)
        if child_sbvalue:
            sbtype = self.sbvalue.GetTypeName() if self.sbtype == None else None
            return variable(child_sbvalue, None, sbtype)
        raise AttributeError

    def __add__(self, other):
        return int(self) + int(other)
        
    def __sub__(self, other):
        return int(self) - int(other)
        
    def __mul__(self, other):
        return int(self) * int(other)
        
    def __floordiv__(self, other):
        return int(self) // int(other)
        
    def __mod__(self, other):
        return int(self) % int(other)
        
    def __divmod__(self, other):
        return int(self) % int(other)
        
    def __pow__(self, other):
        return int(self) ** int(other)
        
    def __lshift__(self, other):
        return int(self) << int(other)
        
    def __rshift__(self, other):
        return int(self) >> int(other)
        
    def __and__(self, other):
        return int(self) & int(other)
        
    def __xor__(self, other):
        return int(self) ^ int(other)
        
    def __or__(self, other):
        return int(self) | int(other)
        
    def __div__(self, other):
        return int(self) / int(other)
        
    def __truediv__(self, other):
        return int(self) / int(other)
        
    def __iadd__(self, other):
        result = self.__add__(other)
        self.sbvalue.SetValueFromCString (str(result))
        return result
        
    def __isub__(self, other):
        result = self.__sub__(other)
        self.sbvalue.SetValueFromCString (str(result))
        return result
        
    def __imul__(self, other):
        result = self.__mul__(other)
        self.sbvalue.SetValueFromCString (str(result))
        return result
        
    def __idiv__(self, other):
        result = self.__div__(other)
        self.sbvalue.SetValueFromCString (str(result))
        return result
        
    def __itruediv__(self, other):
        result = self.__truediv__(other)
        self.sbvalue.SetValueFromCString (str(result))
        return result
        
    def __ifloordiv__(self, other):
        result =  self.__floordiv__(self, other)
        self.sbvalue.SetValueFromCString (str(result))
        return result
        
    def __imod__(self, other):
        result =  self.__and__(self, other)
        self.sbvalue.SetValueFromCString (str(result))
        return result
        
    def __ipow__(self, other):
        result = self.__pow__(self, other)
        self.sbvalue.SetValueFromCString (str(result))
        return result
        
    def __ipow__(self, other, modulo):
        result = self.__pow__(self, other, modulo)
        self.sbvalue.SetValueFromCString (str(result))
        return result
        
    def __ilshift__(self, other):
        result = self.__lshift__(self, other)
        self.sbvalue.SetValueFromCString (str(result))
        return result
        
    def __irshift__(self, other):
        result =  self.__rshift__(self, other)
        self.sbvalue.SetValueFromCString (str(result))
        return result
        
    def __iand__(self, other):
        result =  self.__and__(self, other)
        self.sbvalue.SetValueFromCString (str(result))
        return result
        
    def __ixor__(self, other):
        result =  self.__xor__(self, other)
        self.sbvalue.SetValueFromCString (str(result))
        return result
        
    def __ior__(self, other):
        result =  self.__ior__(self, other)
        self.sbvalue.SetValueFromCString (str(result))
        return result
        
    def __neg__(self):
        return -int(self)
        
    def __pos__(self):
        return +int(self)
        
    def __abs__(self):
        return abs(int(self))
        
    def __invert__(self):
        return ~int(self)
        
    def __complex__(self):
        return complex (int(self))
        
    def __int__(self):
        return self.sbvalue.GetValueAsSigned()
        
    def __long__(self):
        return self.sbvalue.GetValueAsSigned()
        
    def __float__(self):
        return float (self.sbvalue.GetValueAsSigned())
        
    def __oct__(self):
        return '0%o' % self.sbvalue.GetValueAsSigned()
        
    def __hex__(self):
        return '0x%x' % self.sbvalue.GetValueAsSigned()

    def __len__(self):
        return self.sbvalue.size

    @property
    def struct(self):
        '''struct is reserved in C/C++ so no conflicts with __getattr__'''
        return variable_type(self)

