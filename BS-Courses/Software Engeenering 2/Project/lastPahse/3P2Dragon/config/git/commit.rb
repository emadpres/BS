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
  
  
  def reset
  	if @g==nil 
		return
	end

	@g.reset_hard();
  end

  
end

workingDir = ARGV.shift


#Dir.mkdir(workingDir, 0777) 
Dir.chdir workingDir

g = Cgit.new workingDir
g.commit ""