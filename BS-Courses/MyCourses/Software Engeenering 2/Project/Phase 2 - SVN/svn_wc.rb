require 'svn_wc'

yconf = Hash.new
yconf['svn_user']              = 'test_user'
yconf['svn_pass']              = 'test_pass'
yconf['svn_repo_master']       = 'svn+ssh://www.example.com/svn_repository'
yconf['svn_repo_working_copy'] = '/opt/svn_repo'

# 'do_checkout' is only needed until the local repository exists. (i.e. usually first time run only)
# 'force' will plow over anything that may exist at the path.
# i.e. if you ask for a do_checkout without force and the local repo exists, the call will fail

svn = SvnWc::RepoAccess.new(YAML::dump(yconf), do_checkout=true, force=true)

puts svn.svn_repo_master       # 'svn+ssh://www.example.com/svn_repository'
puts svn.svn_user              # 'test_user'
puts svn.svn_pass              # 'test_pass'
puts svn.svn_repo_working_copy # '/opt/svn_repo'

info = svn.info                # another way
puts info[:root_url]           # 'svn+ssh://www.example.com/svn_repository'

file = Tempfile.new('tmp', svn.svn_repo_working_copy).path
begin
  svn.info(file)
# SvnWc::RepoAccess' generic exeception class (the only one, raised for all exceptions)
rescue SvnWc::RepoAccessError => e
  puts e.message.match(/is not under version control/)
end

svn.add file

puts svn.commit file               # returns the revision number of the commit

puts svn.status file               # ' ' empty string, file is current

File.open(file, 'a') {|f| f.write('adding this to file.')}

puts svn.status(file)[0][:status]  # 'M' (modified)
# or, whole repo, multiple entries
svn_wc.status.each do |entries|
  puts "#{entries[:status]}\t#{entries[:path]}"
end

puts svn.info(file)[:rev]          # current revision of file
svn_wc.info(file).each_key do |entries|
  puts entries[:rev]
  puts entries[:last_changed_author]
  puts entries[:last_changed_rev]
end

svn.revert file
svn.commit file                    # -1 i.e commit failed, file is current

svn.delete file
svn.commit file                    # must commit our delete
