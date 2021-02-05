require 'rubygems'
require 'git'

puts '-------------------------------\n'

# Clones the ruby-git repository to the current working directory
#g = Git.clone('https://emadpres@bitbucket.org/emadpres/dark-cube-ii.git', 'ruby-git')
g = Git.open('C:\UDK\UDK-2012-02\Development\Src\Dark-Cube\Classes')

puts '-------------------------------\n'

# Displays the recent commits' author and message.
g.log.each { |l| puts "#{g.gcommit(l).message} | #{g.gcommit(l).author.name}" }

puts '-------------------------------\n'

# Displays 10 files and the stage which they're in.
puts '---------------------'
i = 0
g.status.each do |f|
  puts "#{f.path}\t#{f.stage}" if i < 10 
  i += 1
end


# Shows directories in the root dir.
tree = g.gtree("HEAD^{tree}")
puts '---------------------'
puts tree.subtrees


# Shows the diff patch of last commit and another one.
last_three_commits = []
g.log(3).each { |l| last_three_commits.push(g.gcommit(l)) }
puts '---------------------'
puts g.diff(last_three_commits[0], last_three_commits[2]).patch


# Add a file and commit.
puts '---------------------'
target = File.open('ruby-git/test', 'w')
target.write("This is for testing purpose.\n")
target.close
g.add('test')
g.commit('Here goes the message.')
