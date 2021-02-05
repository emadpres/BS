from django.conf.urls import patterns, include, url

# Uncomment the next two lines to enable the admin:
from django.contrib import admin
admin.autodiscover()

urlpatterns = patterns('',
    # Examples:
	url(r'^$', 'web.views.home'),
	url(r'^News/$', 'web.views.news_home'),
	url(r'^News/(?P<item_id>\d+)/$', 'web.views.news_detail'),
	url(r'^Papers/$', 'web.views.papers_home'),
	url(r'^Papers/(?P<item_id>\d+)/$', 'web.views.papers_detail'),
	url(r'^Outputs/$', 'web.views.outputs_home'),
	url(r'^Outputs/(?P<item_id>\d+)/$', 'web.views.outputs_detail'),
	url(r'^Achievements/$', 'web.views.achievements_home'),
	url(r'^Achievements/(?P<item_id>\d+)/$', 'web.views.achievements_detail'),
    # url(r'^$', 'grc_site.views.home', name='home'),
    # url(r'^grc_site/', include('grc_site.foo.urls')),

    # Uncomment the admin/doc line below to enable admin documentation:
    # url(r'^admin/doc/', include('django.contrib.admindocs.urls')),

    # Uncomment the next line to enable the admin:
	url(r'^admin/', include(admin.site.urls)),
)
