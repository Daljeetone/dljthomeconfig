#!/usr/bin/env python

specs = {
	'FactoryLLDiagsExtras' :
		{ 
			'svn-base' : 'svn+ssh://svn.apple.com/svn/puzzlebox/FactoryLLDiagsExtras/',
		},
	'FactoryLLDiags' : 
		{
			'svn-base' : 'svn+ssh://svn.apple.com/svn/puzzlebox/FactoryLLDiags/'
		}
}

def svn_branch_path(project):
	return specs[project]['svn-base'] + 'branches/'
	
def svn_tag_path(project):
	return specs[project]['svn-base'] + 'tags/'
