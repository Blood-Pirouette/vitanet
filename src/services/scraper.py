from bs4 import BeautifulSoup

def get_search_results(markup):
    soup = BeautifulSoup(markup, "html.parser")
    search_results = soup.find_all("div", class_="mw-search-result-heading")
    extracted_search_results = []
    for item in search_results:
        a_tag = item.find('a')
        title = a_tag.get('title')
        url_link = a_tag.get('href')
        extracted_search_results.append((title, url_link))
    print(extracted_search_results)
    return extracted_search_results

def get_article(markup):
    soup = BeautifulSoup(markup, 'html.parser')
    data = {}
    for item in soup.find_all(['h2', 'p']):
        if item.name == 'h2':
            current_header = item.get_text()
            data[current_header] = []
        if item.name == 'p':
            data[current_header].append(item.get_text())
    return data
