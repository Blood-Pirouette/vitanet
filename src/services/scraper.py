from bs4 import BeautifulSoup



# function to get categories
def get_categories(markup):
    # The variable markup exists in the global namespace before execution
    soup = BeautifulSoup(markup, 'html.parser')
    categories = soup.find('ul', class_='nav nav-list')
    category_items = categories.find_all('li')
    category_items_text = []
    for item in category_items:
        cleaned_text = ' '.join(item.text.split())
        category_items_text.append(cleaned_text)
    return category_items_text

