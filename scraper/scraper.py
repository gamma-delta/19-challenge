"""
I did not want to download and extract all those primes by hand.
So I wrote Python to do it for me!
"""

import io
from bs4 import BeautifulSoup
import requests
from requests_futures.sessions import FuturesSession
from concurrent.futures import as_completed
import py7zr


def response_hook(resp: requests.Response, *args, **kwargs):
    print('Getting', resp.url)
    # The 7zip library requires a file-like object.
    # So let's put it into one
    filent = io.BytesIO(resp.content)
    with py7zr.SevenZipFile(filent) as archive:
        archive.extractall("../primes")
        print('Extracted', resp.url)


page = requests.get("http://www.primos.mat.br/Ate100G_en.html").text
soup = BeautifulSoup(page, "html.parser")

links = []
for entry in soup.find_all("li"):
    link = entry.a["href"]
    link = "http://www.primos.mat.br/" + link
    links.append(link)

print(f"Found {len(links)} files to download")

with FuturesSession() as session:
    session.hooks["response"] = response_hook
    futures = [session.get(link) for link in links]
    for future in as_completed(futures):
        pass  # just make sure to iterate thru it all
