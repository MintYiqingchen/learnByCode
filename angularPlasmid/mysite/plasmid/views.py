from django.shortcuts import render
from django.http import HttpResponse
import json
def index(request):
    return render(request, 'test.html')
# Create your views here.

def data(request):
	with open('plasmid/plasmidData.json') as f:
		data=json.load(f)
	print(len(data))
	return HttpResponse(json.dumps(data),content_type="application/json")