from web.models import News, Papers, Outputs, Achievements
from django import forms
from django.contrib import admin

class NewsForm ( forms.ModelForm ):
	class Meta:
		model = News
		widgets = {
		'summary' : forms.Textarea(attrs={'cols': 80, 'rows': 5}),
		'text': forms.Textarea(attrs={'cols': 80, 'rows': 20}),
		}
	
class NewsCustoms ( admin.ModelAdmin):
	form = NewsForm
	fieldsets = (
        ('Main Info', {
            'fields': ('title','summary', 'text', 'date'),
			'classes': ('NewsForm',)
        }),
	)

class PapersForm ( forms.ModelForm ):
	class Meta:
		model = Papers
		widgets = {
		'summary' : forms.Textarea(attrs={'cols': 80, 'rows': 5}),
		'abstract': forms.Textarea(attrs={'cols': 80, 'rows': 20}),
		}

class PapersCustoms ( admin.ModelAdmin):
	form = PapersForm
	fieldsets = (
        ('Main Info', {
            'fields': ('title','authors','summary', 'abstract', 'date', 'pdf'),
			'classes': ('PapersForm',)
        }),
	)
	


class OutputsForm( forms.ModelForm ):
	class Meta:
		model = Outputs
		widgets = {
		'text': forms.Textarea(attrs={'cols': 80, 'rows': 20}),
		}

class outputCustom(admin.ModelAdmin):
	form = OutputsForm

class AchievementsForm(forms.ModelForm):
	class Meta:
		model = Achievements
		widgets = {
		'text': forms.Textarea(attrs={'cols': 40, 'rows': 20}),
		}
		
class AchievementsCustom(admin.ModelAdmin):	
	form = AchievementsForm

admin.site.register(News, NewsCustoms)
admin.site.register(Outputs, outputCustom)
admin.site.register(Papers, PapersCustoms)
admin.site.register(Achievements, AchievementsCustom)

