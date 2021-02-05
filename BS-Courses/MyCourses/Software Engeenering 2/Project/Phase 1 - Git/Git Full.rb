require 'rubygems'
require 'git'




#g = Git.clone('https://emadpres@bitbucket.org/emadpres/dark-cube-ii.git', 'ruby-git') # Clones the ruby-git repository to the current working directory
g = Git.open('C:\UDK\UDK-2012-02\Development\Src\Dark-Cube\Classes')

puts g
puts g.index
puts g.index.readable?
puts g.index.writable?
puts g.repo
puts g.dir
#puts g.log   # returns array of Git::Commit objects
#puts g.log.since('4 weeks ago')
#puts g.log.between('v2.5', 'v2.6')
g.log.each {|l| puts l.sha }
g.log.each { |l| puts "#{g.gcommit(l).message} | #{g.gcommit(l).author.name}" } # Displays the recent commits' author and message.




=begin
# Shows the diff patch of last commit and another one.
last_three_commits = []
g.log(3).each { |l| last_three_commits.push(g.gcommit(l)) }
puts '---------------------'
puts g.diff(last_three_commits[0], last_three_commits[2]).patch



puts '---------------------'
i = 0 # Displays 10 files and the stage which they're in.
g.status.each do |f|
    puts "#{f.path}\t#{f.stage}" if i < 10 
	i += 1
end
=end

#puts '------'
#puts g.object('HEAD^').contents

puts '---------------------'
tree = g.gtree("HEAD^{tree}")
puts tree.subtrees

puts '---------------------'
commit = g.gcommit(g.log(1))
puts 'Commit=',commit
puts commit.gtree
puts commit.parent.sha
puts commit.parents.size
puts commit.author.name
puts commit.author.email
puts commit.author.date.strftime("%m-%d-%y")
puts commit.committer.name
puts commit.date.strftime("%m-%d-%y")
puts commit.message



=begin
puts g.gtree("HEAD^{tree}")
puts g.gblob("HEAD^{tree}")
puts g.gcommit("HEAD^{tree}")
=end


