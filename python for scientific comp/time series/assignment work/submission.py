import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from statsmodels.tsa.seasonal import seasonal_decompose
from statsmodels.tsa.stattools import adfuller

# Load the dataset
df = pd.read_csv('dataset_11.csv')

# Convert eventDate to datetime format
df['eventDate'] = pd.to_datetime(df['eventDate'], errors='coerce')

# Ensure 'individualCount' is numeric and handle missing values
df['individualCount'] = pd.to_numeric(df['individualCount'], errors='coerce')

# Forward fill missing values and fill remaining with 0
df['individualCount'] = df['individualCount'].ffill().fillna(0)

# Check if the column is constant
if df['individualCount'].nunique() == 1:
    print("Error: 'individualCount' column is constant. Cannot proceed with analysis.")
    print("Unique values:", df['individualCount'].unique())
    print("Value counts:\n", df['individualCount'].value_counts())
else:
    # Proceed with time series analysis
    print("Proceeding with time series analysis...")
    
    # Plot the time series
    plt.figure(figsize=(10, 5))
    plt.plot(df['eventDate'], df['individualCount'])
    plt.xlabel('Date')
    plt.ylabel('Individual Count')
    plt.title('Individual Count Over Time')
    plt.show()

    # Perform decomposition
    try:
        decomposition = seasonal_decompose(df.set_index('eventDate')['individualCount'], model='additive', period=12)
        decomposition.plot()
        plt.show()
    except ValueError as e:
        print("Error during decomposition:", e)

    # Perform Augmented Dickey-Fuller Test
    adf_result = adfuller(df['individualCount'].dropna())
    print("ADF Statistic:", adf_result[0])
    print("p-value:", adf_result[1])
    for key, value in adf_result[4].items():
        print(f"Critical Value ({key}): {value}")
