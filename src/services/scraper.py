from bs4 import BeautifulSoup

# The variable markup exists in the global namespace before execution
soup = BeautifulSoup(markup, 'html.parser')

# Extract the title of the webpage
title_object = soup.title
if title_object:
    result = title_object.text
    result = result.encode('utf-8')
else:
    result = 'No title found in the html'
