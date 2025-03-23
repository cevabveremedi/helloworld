# Ahmet Suat Kartal
# 210401134

import time
import random
import matplotlib.pyplot as plt

# Bubble Sort algoritmasi
def bubble_sort(arr):
    n = len(arr)
    # Dizi uzerinde tekrar eden donguler
    for i in range(n - 1):
        # Siradaki cift elemanlar karsilastirilir ve gerekirse yer degistirilir
        for j in range(n - i - 1):
            if arr[j] > arr[j + 1]:
                # Elemanlarin yeri degistiriliyor
                arr[j], arr[j + 1] = arr[j + 1], arr[j]

# Insertion Sort algoritmasi
def insertion_sort(arr):
    # Dizinin ikinci elemanindan itibaren ilerler
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        # Siralanan kisimdaki uygun yeri bulur
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        # Anahtari uygun yere yerlestirir
        arr[j + 1] = key

# Verilen siralama fonksiyonunun calisma suresini olcer
def measure_time(sort_function, arr):
    start_time = time.time()
    sort_function(arr)
    end_time = time.time()
    return end_time - start_time

# Test edilecek dizi boyutlari
array_sizes = [100, 500, 1000, 2000, 5000]

# Sonuclar icin zaman listeleri
bubble_times = []
insertion_times = []

# Bubble Sort performans testi
print("Bubble Sort Performans Testi")
for size in array_sizes:
    # Rastgele dizi olusturuluyor
    test_array = [random.randint(0, 10000) for _ in range(size)]
    
    # Bubble sort calistirilir ve suresi olculur
    bubble_time = measure_time(bubble_sort, test_array.copy())
    print(f"Dizi Boyutu: {size} - Bubble Sort Sure: {bubble_time:.6f} saniye")
    bubble_times.append(bubble_time)

print("\nInsertion Sort Performans Testi")
for size in array_sizes:
    # Rastgele dizi olusturuluyor
    test_array = [random.randint(0, 10000) for _ in range(size)]
    
    # Insertion sort calistirilir ve suresi olculur
    insertion_time = measure_time(insertion_sort, test_array.copy())
    print(f"Dizi Boyutu: {size} - Insertion Sort Sure: {insertion_time:.6f} saniye")
    insertion_times.append(insertion_time)

# Sonuclari grafik uzerinde gosterir (Kaynak: ChatGPT)
plt.figure(figsize=(10, 6))  # Grafik boyutu belirlenir
plt.plot(array_sizes, bubble_times, marker='o', linestyle='-', color='b', label="Bubble Sort")
plt.plot(array_sizes, insertion_times, marker='s', linestyle='--', color='r', label="Insertion Sort")
plt.xlabel("Dizi Boyutu")  # X ekseni etiketi
plt.ylabel("Calisma Suresi (saniye)")  # Y ekseni etiketi
plt.title("Bubble Sort vs Insertion Sort Zaman Karsilastirmasi")  # Grafik basligi
plt.legend()  # Aciklama etiketi
plt.grid(True)  # Izgara eklenir
plt.show()  # Grafik gosterilir