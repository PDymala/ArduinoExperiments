from django.urls import path, include
from . import views

app_name = 'server'

urlpatterns = [
    path('', views.index, name='index'),

]