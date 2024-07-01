from bs4 import BeautifulSoup

# The variable markup exists in the global namespace before execution
soup = BeautifulSoup(markup, 'html.parser')

categories = soup.find('ul', class_='nav nav-list')

category_items = categories.find_all('li')
category_items_text = []
for item in category_items:
    cleaned_text = ' '.join(item.text.split())
    category_items_text.append(cleaned_text)


# Extract the title of the webpage
title_object = soup.title
if title_object:
    result = title_object.text
    result = result.encode('utf-8')
else:
    result = 'No title found in the html'
