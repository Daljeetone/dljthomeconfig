#!/usr/bin/env python

import sys, shlex, subprocess

def execute_command(cmdline, ignore_errors=False):
	#sys.stdout.write('\nCMD: '+cmdline+'\n' if verbose else '')
	streams = subprocess.Popen(shlex.split(cmdline), stdout=subprocess.PIPE, stderr=subprocess.PIPE).communicate()
	
	if not ignore_errors:
		if streams[1]:
			#if STDERR output exists notify and exit
			print >> sys.stderr, 'An Error Occured while running cmd: ' + cmdline + '\n'
			print >> sys.stderr, streams[1]
			return None
	
	#sys.stdout.write('OUT:\n' + streams[0] + '**END**\n' if verbose else '')
	
	return streams[0]

def check_svn_path_exists(path):
	cmd = 'svn info %s' % path
	
	# Ignore any errors if the path does not exist
	output = execute_command(cmd, True)
	
	if('' == output or None == output):
		return False
		
	return True

def get_version(update, project):
	cmd = '/Network/Servers/xs1/release/bin/listProjectVersions -update %s %s' % (update, project)	
	output = execute_command(cmd).strip().splitlines()[2].split()[1]
	
	#if verbose:
	print "%s had %s" % (update, output)
	
	return output.strip()

def latest_branch_version(svnbase, version):
	dot_version = 1
	if('.' in version):
		idx = version.rfind('.')
		dot_version = int(version[idx+1:]) + 1
		version = version[:idx]

	#if verbose:
	#print "initial dot-version: %d" % dot_version

	# find the value after the dot and increment it
	while(True):
		check_version = "%s.%d" % (version, dot_version)
		if not check_svn_path_exists(svnbase + 'tags/' + check_version):
			version = "%s.%d" % (version, dot_version-1)
			break
			
		dot_version = dot_version + 1

	#if verbose:
	#print "cur-tag: %s" % version
	return version

def next_branch_version(svnbase, version):
	dot_version = 1
	if('.' in version):
		idx = version.rfind('.')
		dot_version = int(version[idx+1:]) + 1
		version = version[:idx]

	#if verbose:
	#print "initial dot-version: %d" % dot_version

	# find the value after the dot and increment it
	while(True):
		check_version = "%s.%d" % (version, dot_version)
		if not check_svn_path_exists(svnbase + 'tags/' + check_version):
			version = check_version
			break

		dot_version = dot_version + 1

	#if verbose:
	#print "next-tag: %s" % version

	return version
	
def get_tag_revision(path):
	cmd = 'svn info %s' % path
	# pick up the "Last revision:" line
	output = execute_command(cmd).strip().splitlines()[7]
	
	index = output.find(':')
	rev = output[index+2:].strip()
		
	return int(rev)


