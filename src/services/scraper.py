from bs4 import BeautifulSoup


# function to get categories
def get_categories(markup):
    # The variable markup exists in the global namespace before execution
    soup = BeautifulSoup(markup, 'html.parser')
    categories = soup.find('ul', class_='nav nav-list')
    category_items = categories.find_all('li')
    extracted_category_items = []
    for item in category_items:
        cleaned_text = ' '.join(item.text.split())
        a_tag = item.find('a')
        url_link = a_tag.get('href')
        extracted_category_items.append((cleaned_text,url_link))
    return extracted_category_items

