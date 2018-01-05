#!/usr/bin/env python

import sys, shlex, subprocess
import getopt
import os
import branches
from rc import *

dryrun = False

def usage():
	print "todo..."
	sys.exit(0)

def main():
	global verbose, dryrun
	
	try:
		opts, args = getopt.getopt(sys.argv[1:], 'ht:p:b:',
                                   ['help',   'train=',  'project=', 'base='])
	except getopt.GetoptError, err:
		# print help information and exit on unsupported options
		print str(err)
		usage()
		sys.exit(2)

	if args and not opts:
		# print help and exit on non-options
		usage()
		sys.exit()
	
	override_release = None
	
	for o, a in opts:
		if o in ('-h', '--help'):
			usage()
			sys.exit()
		elif o in ('-t', '--train'):
			build_train = a
		elif o in ('-p', '--project'):
			project = a
		elif o in ('-b', '--base-release'):
			override_release = a
		else:
			assert False, 'unhandled option'
	
	if(None != override_release):
		release = override_release
	else:
		release = "Current%s" % build_train
		
	print "Train: %s" % build_train
	print "Project: %s" % project
	print "Base-Release: %s" % release
	
	current_ver = get_version(release, project)
	
	print "Current Ver: %s" % current_ver
	
	version = next_branch_version(branches.specs[project]['svn-base'], current_ver)
	cur_version = latest_branch_version(branches.specs[project]['svn-base'], current_ver)
	
	print "cur ver: %s" % cur_version
	print "next ver: %s" % version
	
	cmd = 'svn cp ' + branches.svn_branch_path(project) + build_train + ' ' + branches.svn_tag_path(project) + version + " -m 'Tagging %s from %s for submission to %s'" % (version, branches.svn_branch_path(project) + build_train, build_train)
	
	print "CMD: %s" % cmd
	
	#output = execute_command(cmd)
	
	rev = get_tag_revision(branches.svn_tag_path(project) + current_ver)
	
	cmd = "svn log --stop-on-copy -r%d:HEAD %s" % (rev, branches.svn_branch_path(project) + build_train)
	print "CMD: %s" % cmd
	log = execute_command(cmd)
	
	print ""
	print "Changelist:"
	lines = log.splitlines()
	radars = []
	for line in lines:
		if line.find('rdar://') != -1:
			radars.append(line)
			
	for r in set(radars):
		print r
	
	print ""
	print "Submission Command:"
	print "~rc/bin/submitproject -url " + branches.svn_tag_path(project) + version + " " + build_train
	
	return 0


if __name__ == '__main__':
    main()