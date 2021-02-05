require 'rubygems'
require 'git'

class Cgit  

  def initialize(gAddress)  #Constructor Try to Open given existing repo path
	begin
		@g=nil
		@gAddress = gAddress
		@g = Git.open(gAddress)
	rescue StandardError => e
		puts 'Error in Opening Repository:'
		puts 'Path is not Accessible !'
		#puts e.message
		return -1 #Error
	else
		puts 'Git has been Opened Succesfully !'
	end
  end  
  
  def initGitRepo(gAddress)
	@gAddress = gAddress
  	@g = Git.init(gAddress)
	puts 'New Repo created !'
  end
  
  def clone(gAddress) # 'https://emadpres@bitbucket.org/emadpres/dark-cube-ii.git'
	@g = Git.clone(gAddress, 'ruby-git') # Clones the ruby-git repository to the current working directory
	username='emadpres'
	email='emadpres@gmail.com'
	config(username, email)
  end
  
  def config(username, email)
  	if @g==nil 
		return
	end

	@g.config('user.name', username)
	@g.config('user.email', email)  
  end
  
  def recentCommits
  	if @g==nil 
		return
	end

	puts '>>>> Recent Commits'
	@g.log.each { |l| puts "#{@g.gcommit(l).message} | #{@g.gcommit(l).author.name}" }
  end
  
  def getStatus
	if @g==nil 
		return
	end
	puts @gAddress
	puts @g.current_branch() #Current Branch Name
	puts @g.remotes #Currnet Remote Name
	#puts @g.status.pretty
	puts '-------- STATUS -----'
	puts ' +++++++++ '
	puts '>New File:'
	puts @g.status.added.keys #each { |l| puts l }
	
	puts ' --------- '
	puts '>Changed:'
	puts @g.status.changed.keys
	puts '>Deleted:'
	puts @g.status.deleted.keys
	puts '>Untracked:'
	puts @g.status.untracked.keys
	puts '-------- ------ -----'
  end
  
  def add(fileName)
  	if @g==nil 
		return
	end

	begin
		@g.add(fileName)
	rescue Git::GitExecuteError => e
		puts 'Your File is not Accessible !'
		#puts "Error in adding file :"
		#puts e.message
		return -1 #Error
	else
		puts fileName+'  >> File Added Succesfully !'
	end
  end
  
  def remove(fileName)
  	if @g==nil 
		return
	end

	begin
	@g.remove(fileName)
	rescue Git::GitExecuteError => e
		puts 'Your File is not Accessible !'
		#puts "Error in Removing file :"
		#puts e.message
		return -1 #Error
	else
		puts fileName+'  >> File Removed Succesfully (Sorry, It removed even From HDD ) !'
	end
  end

  def commit(message)
  	if @g==nil 
		return
	end

	begin
		@g.commit(message)
	rescue Git::GitExecuteError => e
		puts 'Error in Commit !'
		puts 'Nothing Added for Commit !'
		puts e.message
		return -1 #Error
	else
		puts 'Commit Done Succesfully !'
	end
  end
  
  def push(add)
	if @g==nil 
		return
	end
	begin
		puts 'Enter password in order to push'
		@g.push(add)
	rescue Git::GitExecuteError => e
		puts 'Error in Pushing !'
		puts 'Check Your Internet Conncetion Or Password, and Try Again please!'
		puts e.message
		return -1 #Error
	else
		puts 'Push Done Succesfully !'
	end
  end
  
  
  def pull(gAdd)
  	if @g==nil 
		return
	end

	begin
	  puts 'Enter password'
	  ret = @g.pull(gAdd)
		if(ret == nil )
			puts("nil returned")
		else
			puts "return of Pull:",ret
		end
	rescue Git::GitExecuteError => e
		puts 'Error in Pulling !'
		puts 'Check Your Internet Conncetion Or Password, and Try Again please!'
		puts e.message
		return -1 #Error
	else
		puts 'Pull Done Succesfully !'
	end
  end
  
  def fig1
	c={}
	#@g.log.each { |l| puts ">>",l,"  >>>#{@g.gcommit(l).message} | #{@g.gcommit(l).author.name}" }
	@g.log.each do |l|
		#puts l,"  >>>#{@g.gcommit(l).message} | #{@g.gcommit(l).author.name}"
		if c[@g.gcommit(l).author.name]==nil
			c[@g.gcommit(l).author.name]=1
		else
			c[@g.gcommit(l).author.name] = c[@g.gcommit(l).author.name] + 1 
		end
	end
	#puts c
	return c
end
 
def fig2
	c={}
	first=true
	lc1=nil
	lc2=nil
	@g.log.each do |l|
		if first
			#puts "First"
			first=false
			lc2=l
		else
			lc1=lc2
			lc2=l
			#puts @g.gcommit(lc1).author.name
			if c[@g.gcommit(lc1).author.name]==nil
				c[@g.gcommit(lc1).author.name]={}
			end
			changedFileArray = @g.diff(lc1,lc2).stats[:files].keys
			for f in changedFileArray do
				if c[@g.gcommit(lc1).author.name][f]==nil
					c[@g.gcommit(lc1).author.name][f]=1
				else
					c[@g.gcommit(lc1).author.name][f] = c[@g.gcommit(lc1).author.name][f]  + 1
				end
			end
				
		end
		
		#puts l1,"  ",l2
		#puts @g.gcommit(l1).gtree.blobs.keys
		#puts @g.gcommit(l2).gtree.blobs.keys
	end
	return c
=begin
 
  
	#@g.log.each { |l| puts "#{@g.gcommit(l).message} | #{@g.gcommit(l).author.name}" }
	#puts @g.gcommit('HEAD^^^').date.strftime("%m-%d-%y")
	
	tree = @g.gtree('HEAD') # gtree('HEAD{tree}')
	puts "tree:",tree,''
	puts "Blobs:",tree.blobs #   =  puts "Children:",tree.children
	puts "Files:"
	tree.blobs.each do |key, value|  #tree.blobs.each {	|a,b| puts "++ "+a+"  -- " }
						puts "++ "+key+"  -- "+value.sha
					end
	
	
	lc = @g.gcommit('HEAD')
	lc2 = @g.gcommit('HEAD^')
	puts "\nlast commit: ",lc
	puts "Date: ",lc.date
	puts "Name: ",lc.name
	puts "Parent: ",lc.parents
	puts "GTree: ",lc.gtree
	lc.gtree.blobs.each do |key, value|  #tree.blobs.each {	|a,b| puts "++ "+a+"  -- " }
						puts "++ "+key+"  -- "+value.sha
					end
					
	puts ''
	puts @g.diff(lc,lc2).stats#[:total][:lines]
	
    #puts tree.blobs.keys
    #puts tree.subtrees
    #puts tree.children # blobs and subtrees
	
	#puts @g.diff('HEAD','HEAD^^^').stats
	#@g.gtree('HEAD^')
	#puts @g.object('HEAD^').contents
	#@g.diff.each { |l| puts l}
=end	

end
  
  
  def reset
  	if @g==nil 
		return
	end

	@g.reset_hard();
  end

  
end

######################################################################################################

#test = Cgit.new('D:\University\Lessons\Software Engeenering 2\Project\Phase 1 - Git\SCCS') 
test = Cgit.new('D:\Back-Up\UDK-2012-10-SS\Src\Dark-Cube\Classes')
puts "test: ",test
########################################################################################################
#############################   M Y        T   E   S   T   #############################################
########################################################################################################
#=begin
#test.getStatus
#test.recentCommits
#test.add('Readme.txt')
#test.add('AddFile2.txt')
#test.getStatus

#test.getStatus
puts '<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>'
#test.add('tee.txt');
#test.getStatus

#puts test.fig1 # Worked

puts test.fig1
puts  test.fig2



#test.getStatus
#puts '<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>'
#test.remove('a.txt')
#test.commit('deleting a');
#test.pull('https://emadpres@bitbucket.org/emadpres/software-coding-control-system.git')
#puts '<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>'
#test.getStatus


#test.getStatus

#puts Git::Branch
#test.pull

#	puts 'Enter password'
	#@g.fetch(@g.remotes)
#	puts 'Enter password'
	#@g.pull



#puts test.getStatus
#puts test.add('a.txt');
#puts 'Commit'
#puts test.commit('Here goes the message.')

#puts test.push('https://emadpres@bitbucket.org/emadpres/software-coding-control-system.git')
#=end