require 'rubygems'
require 'git'

#test
#ARGV.each do|a|
 # puts "Argument: #{a}"
#end

#puts ARGV.shift
#end test

workingDir = ARGV.shift
projectName = ARGV.shift
url = ARGV.shift

#Dir.mkdir(workingDir, 0777) 
Dir.chdir workingDir
g = Git.init
g = Git.clone(url, projectName)
