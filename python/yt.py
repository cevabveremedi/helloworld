from time import time
from pytube import YouTube, Playlist
from concurrent.futures import ThreadPoolExecutor, as_completed

playlist_link = "https://youtube.com/playlist?list=PL9cEgowSv_l5ZHKHBOxS9rhnM51uBbOq7&si=sexJkKkS-SRttn0-"
video_links = Playlist(playlist_link).video_urls
start = time()

def get_video_title(link):
    title = YouTube(link).title
    return title

processes = []
with ThreadPoolExecutor(max_workers=10) as executor:
    for url in video_links:
        processes.append(executor.submit(get_video_title, url))

video_titles = []
with open("video_titles.txt", "w") as file:
    for task in as_completed(processes):
        title = task.result()
        video_titles.append(title)
        file.write(title + "\n")
        print(title)

print(f'Time taken: {time() - start}')
