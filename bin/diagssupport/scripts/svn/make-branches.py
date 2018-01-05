#!/usr/bin/env python

import sys, shlex, subprocess
import getopt
import os
import branches
from rc import *

from pprint import pprint

verbose = False
dryrun = False

# Convenience
branch_specs = branches.specs

def do_branching(branch_dict):
	fllde_version = get_version(branch_dict['origin'], 'FactoryLLDiagsExtras')
	fllde_branch_version = next_branch_version(branch_specs['FactoryLLDiagsExtras']['svn-base'], fllde_version)
	
	exists = check_svn_path_exists(branch_specs['FactoryLLDiagsExtras']['svn-base'] + 'branches/' + branch_dict['name'])
	
	if verbose:
		print "branch %s exists: %s" % (branch_dict['name'], 'yes' if exists else 'no')
	
	operations = []
	if exists:
		operations.append('svn rm ' + branch_specs['FactoryLLDiagsExtras']['svn-base'] + 'branches/' + branch_dict['name'])
	
	operations.append('svn cp ' + branch_specs['FactoryLLDiagsExtras']['svn-base'] + 'trunk ' + branch_specs['FactoryLLDiagsExtras']['svn-base'] + 'branches/' + branch_dict['name'])
	
	operations.append('svn tag ' + branch_specs['FactoryLLDiagsExtras']['svn-base'] + 'branches/' + branch_dict['name'] + ' ' + branch_specs['FactoryLLDiagsExtras']['svn-base'] + 'tags/' + fllde_branch_version)
	
	pprint(operations)
	
	## TODO: Perform the operations here.
	
	return 0

def usage():
	print "todo..."
	sys.exit(0)

def main():
	global verbose, dryrun
	
	try:
		opts, args = getopt.getopt(sys.argv[1:], 'h:n:p:vd',
                                   ['help',   'branch-name=',  'branch-point=', 'verbose', 'dryrun'])
	except getopt.GetoptError, err:
		# print help information and exit on unsupported options
		print str(err)
		usage()
		sys.exit(2)

	if args and not opts:
		# print help and exit on non-options
		usage()
		sys.exit()

	branchname=None
	branchpoint=None

	for o, a in opts:
		if o in ('-h', '--help'):
			usage()
			sys.exit()
		elif o in ('-v', '--verbose'):
			verbose = True
		elif o in ('-n', '--branch-name'):
			branchname = a
		elif o in ('-p', '--branch-point'):
			branchpoint = a
		elif o in ('-d', '--dryrun'):
			dryrun = True
		else:
			assert False, 'unhandled option'
		
	if verbose:
		print 'branch-name=%s branch-point=%s' % (branchname, branchpoint)
	
	if(branchname == None):
		print "branch-name required"
		usage()
		sys.exit(1)
	
	if(branchpoint == None):
		print "branch-point required"
		usage()
		sys.exit(1)
	
	branch = {}
	branch['name'] = branchname
	branch['origin'] = branchpoint	
	
	return do_branching(branch)


if __name__ == '__main__':
    main()