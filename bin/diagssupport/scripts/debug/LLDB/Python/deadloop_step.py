import optparse
import shlex
import classes
import os
import re
import sys
from DataStructureDict import *

def dead_step():
  usage = "usage: %prog"
  description='''Steps over EFI_DEADLOOP()'''
  parser = optparse.OptionParser(description=description, prog='deadloop_step',usage=usage)
  return parser


def get_registers(frame, kind):
   '''Returns the registers given the frame and the kind of registers desired.

   Returns None if there's no such kind.
   '''
   registerSet = frame.GetRegisters() # Return type of SBValueList.
   for value in registerSet:
      if kind.lower() in value.GetName().lower():
         return value

   return None

def get_GPRs(frame):
   '''Returns the general purpose registers of the frame as an SBValue.

   The returned SBValue object is iterable.  An example:
       ...
       from lldbutil import get_GPRs
       regs = get_GPRs(frame)
       for reg in regs:
           print '%s => %s' % (reg.GetName(), reg.GetValue())
       ...
   '''
   return get_registers(frame, 'general purpose')

def inc_reg(frame, reg_name):
   regs = get_GPRs(frame)
   for reg in regs:
      if reg.GetName() == reg_name:
         command = "register write %s 0x%x" % (reg.GetName(), int(reg.GetValue(),16) + 1)
         print "Updating register using:", command
         classes.GDebugger.HandleCommand(command)
         return True

   return False

def set_reg(frame, reg_name, value):
   regs = get_GPRs(frame)
   for reg in regs:
      if reg.GetName() == reg_name:
         command = "register write %s 0x%x" % (reg.GetName(), int(value.strip("#"),16))
         print "Updating register using:", command
         classes.GDebugger.HandleCommand(command)
         return True

   return False

def get_instructions(frame):
   instructions = frame.Disassemble()

   offset = instructions.find("-> ")
   if offset < 0:
      print "Could not find disassembly"
      sys.exit()

   instructions = instructions[offset:]
   return instructions

def deadloop_step_command(debugger, command, result, unused):
   
   MaxNumInstr = 14
   classes.init_command(debugger)

   process = classes.GTarget.GetProcess();
   if not process:
      print "No process"
      return 

   thread = process.GetThreadAtIndex(0)

   if not thread:
      print "No thread"
      return 

   frame = thread.GetFrameAtIndex(0)

   instructions = get_instructions(frame);

   cmp_instruction = instructions.splitlines()[0];
   b_instruction = instructions.splitlines()[1];

   if classes.GTarget.addr_size == 8:
      b_pattern = "b.eq"   
   else:
      b_pattern = "bne"   

   i = 0

   while cmp_instruction.find('cmp') < 0 and b_instruction.find(b_pattern) < 0 and i < MaxNumInstr:
      classes.debug_print("Instructions:\n", instructions)
      classes.debug_print("cmp_instruction:", cmp_instruction)
      classes.debug_print("b_instruction:", b_instruction)

      thread.StepInstruction(False)
      frame = thread.GetFrameAtIndex(0)
      instructions = get_instructions(frame);

      cmp_instruction = instructions.splitlines()[0];
      b_instruction = instructions.splitlines()[1];

      i += 1

   if i >= MaxNumInstr:
      print "Did not find cmp function"
      return

   print cmp_instruction
   print b_instruction
   if classes.GTarget.addr_size == 8:
      pattern = re.compile(":\s+cmp\s+([x#]\d),\s+([x#]\d)");
   else:
      pattern = re.compile(":\s+cmp\s+([r#]\d),\s+([r#]\d)");

   match = pattern.search(cmp_instruction);
   if not match:
      print "Did not find needed instruction setup"
      return

   cmp1 = match.group(1);
   cmp2 = match.group(2)
   classes.debug_print("Comparing %s to %s" % (cmp1, cmp2))

   done = False
   if classes.GTarget.addr_size == 8:
      if inc_reg(frame, cmp1):
         done = True
      elif inc_reg(frame, cmp2):
         done = True
   else:
      if set_reg(frame, cmp1, cmp2):
         done = True
      elif inc_reg(frame, cmp2, cmp1):
         done = True

   if not done:
      print "failed change the compared registers"
      return
      
   pc_before = int(frame.GetPCAddress())
   classes.debug_print("pc before = 0x%lx" % pc_before)
   # step twice, once for comp one for branch
   thread.StepInstruction(False)
   thread.StepInstruction(False)
   frame = thread.GetFrameAtIndex(0)
   pc_after = int(frame.GetPCAddress())
   classes.debug_print("pc after = 0x%lx" % pc_after)

   if pc_after > pc_before:
      print "success"
      return
   else:
      print "fail"
      return
