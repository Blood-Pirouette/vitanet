from bs4 import BeautifulSoup

#Declare variable
my_string = ''

# Example HTML
html_string = '<html><head><title>Example Page</title></head><body><h1>Hello, BeautifulSoup!</h1></body></html>'

# Create a BeautifulSoup object
soup = BeautifulSoup(html_string, 'html.parser')

# Extract the title of the webpage
title_object = soup.title
if title_object:
    my_string = title_object.text
    my_string = my_string.encode('utf-8')
else:
    my_string = 'no title found'
