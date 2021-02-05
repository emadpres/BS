from django.db import models
from django_jalali.db import models as jmodels

class News(models.Model):
	title = models.CharField(max_length=100, help_text="All Fields Are Essential")
	summary = models.CharField(max_length=1000)
	text = models.CharField(max_length=10000)
	date = models.DateTimeField('date published')
	#date = jmodels.jDateTimeField('date published') #Jalali Calender
	def __unicode__(self):
		return self.title
	
class Papers(models.Model):
	title = models.CharField(max_length=100, help_text="All Fields Are Essential")
	authors = models.CharField(max_length=100, help_text="Separate with `,` ");
	summary = models.CharField(max_length=1000)
	abstract = models.CharField(max_length=10000)
	date = models.DateTimeField('date published')
	pdf = models.FileField(upload_to='papers', blank=True, help_text="optional - pdf")
	def __unicode__(self):
		return self.title
	
class Outputs(models.Model):
	title = models.CharField(max_length=100, help_text="All Fields Are Essential")
	summary = models.CharField(max_length=1000)
	picture_small = models.FileField(upload_to='Thumb', help_text="100x100")
	text = models.CharField(max_length=10000, blank=True)
	platrformChoice = (
    ('Windows', 'Windows'),
    ('Linux', 'Linux'),
    ('Mac', 'Mac'),
	('iOS', 'iOS'),
    ('Android', 'Android'),
	('Other', 'Other'),
	)
	platrform = models.CharField(max_length=20, choices=platrformChoice , blank=True)
	date = models.DateTimeField('date published')
	teamLeader = models.CharField(max_length=50, blank=True)
	teamMembers = models.CharField(max_length=500, blank=True)
	binaryFile = models.FileField(upload_to='binary', blank=True, help_text="Setup.exe")
	picture1 = models.FileField(upload_to='Outputs_picture', blank=True, help_text="500x500")
	picture2 = models.FileField(upload_to='Outputs_picture', blank=True, help_text="400x400")
	picture3 = models.FileField(upload_to='Outputs_picture', blank=True, help_text="300x300")
	def __unicode__(self):
		return self.title
		
class Achievements(models.Model):
	title = models.CharField(max_length=100, help_text="All Fields Are Essential")
	text = models.CharField(max_length=1000)
	date = models.DateTimeField('Date')
	def __unicode__(self):
		return self.title