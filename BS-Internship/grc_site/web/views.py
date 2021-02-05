from django.http import HttpResponse
from django.template import Context, loader
from web.models import News, Papers, Outputs, Achievements

def home(request):
	test = 'test'
	t = loader.get_template('home.html')
	c = Context({'test':test})
	return HttpResponse(t.render(c))
	
	
def news_home(request):
	allNews = News.objects.all().order_by('date')
	t = loader.get_template('news.html')
	c = Context({'allNews':allNews})
	return HttpResponse(t.render(c))

def news_detail(request, item_id):
	news_id = int(item_id)
	if news_id > News.objects.all().count() or news_id<=0 :
		return HttpResponse('')
	theNews = News.objects.all()[news_id-1]
	t = loader.get_template('news_detail.html')
	c = Context({'theNews':theNews})
	return HttpResponse(t.render(c))

def papers_home(request):
	allPapers = Papers.objects.all().order_by('date')
	t = loader.get_template('papers.html')
	c = Context({'allPapers':allPapers})
	return HttpResponse(t.render(c))

		
def papers_detail(request, item_id):
	item_id = int(item_id)
	if item_id > Papers.objects.all().count() or item_id<=0 :
		return HttpResponse('')
	thePaper = Papers.objects.all()[item_id-1]
	t = loader.get_template('papers_detail.html')
	c = Context({'thePaper':thePaper})
	return HttpResponse(t.render(c))

	


def outputs_home(request):
	allOutputs = Outputs.objects.all()
	t = loader.get_template('outputs.html')
	c = Context({'allOutputs':allOutputs})
	return HttpResponse(t.render(c))
	
def outputs_detail(request, item_id):
	item_id = int(item_id)
	if item_id > Outputs.objects.all().count() or item_id<=0 :
		return HttpResponse('')
	theOutput = Outputs.objects.all()[item_id-1]
	t = loader.get_template('outputs_detail.html')
	c = Context({'theOutput':theOutput})
	return HttpResponse(t.render(c))

	
	
def achievements_home(request):
	allAchievements = Achievements.objects.all()
	t = loader.get_template('achievements.html')
	c = Context({'allAchievements':allAchievements})
	return HttpResponse(t.render(c))

def achievements_detail(request, item_id):
	item_id = int(item_id)
	if item_id > Achievements.objects.all().count() or item_id<=0 :
		return HttpResponse('')
	theAchievement = Achievements.objects.all()[item_id-1]
	t = loader.get_template('achievements_detail.html')
	c = Context({'theAchievement':theAchievement})
	return HttpResponse(t.render(c))
	
	