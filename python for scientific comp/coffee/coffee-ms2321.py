import pandas as pd
import matplotlib.pyplot as plt
from collections import Counter




# Load the dataset
df = pd.read_csv('coffee_survey.csv')

# b. Analyze bitterness preference across different age groups
# Group by age and calculate mean bitterness preference
bitterness_by_age = df.groupby('age')['coffee_a_bitterness'].mean()
#print("\nBitterness preference across different age groups:")
#print(bitterness_by_age)

bitterness_by_age.plot(kind='bar')
plt.xlabel('Age')
plt.ylabel('Mean Bitterness Preference')
plt.title('Bitterness Preference by Age Group')
plt.show()

#----------------------#

# Define the categories and their corresponding percentages
categories = ['At Home', 'At Office', 'At a Cafe', 'On the Go', 'None of These']
percentages = [70, 15, 8, 5, 2]  # Example percentages

# Plotting the bar chart
plt.figure(figsize=(10, 6))
plt.barh(categories, percentages, color='skyblue')
plt.xlabel('Percentage (%)')
plt.ylabel('Brew Location')
plt.title('Where do you brew coffee?')
plt.xlim(0, 100)  # Setting x-axis from 0% to 100%

# Adding the percentage labels on the bars
for index, value in enumerate(percentages):
    plt.text(value + 1, index, f'{value}%', va='center')

plt.show()



# Example dataset loaded into a DataFrame
data = {
    'brew': [
        "Pod/capsule machine (e.g. Keurig/Nespresso), Espresso, French press",
        "Pour over, French press, Espresso, Instant coffee, Pod/capsule machine (e.g. Keurig/Nespresso)",
        "Pour over, Coffee brewing machine (e.g. Mr. Coffee), Espresso, Bean-to-cup machine",
        "Pour over, Espresso, Instant coffee",
        "Pour over, Coffee brewing machine (e.g. Mr. Coffee)",
        "Pour over",
        "Other",
        "Espresso",
        "Coffee extract (e.g. Cometeer)",
        "Pour over",
        "Pod/capsule machine (e.g. Keurig/Nespresso), French press",
        "Pour over, Espresso",
        "Espresso, Cold brew, Pour over",
        "French press, Cold brew",
        "Pour over, Espresso",
        "Pour over"
    ]
}

# Load the data into a DataFrame
df = pd.DataFrame(data)

# Replace terms with standardized keywords
brew_mapping = {
    'Pod/capsule machine (e.g. Keurig/Nespresso)': 'Pod Machine',
    'Espresso': 'Espresso',
    'French press': 'French Press',
    'Pour over': 'Pour-over',
    'Coffee brewing machine (e.g. Mr. Coffee)': 'Mr. Coffee',
    'Cold brew': 'Cold Brew',
    'Coffee extract (e.g. Cometeer)': 'Cometeer',
    'Instant coffee': 'Instant Coffee',
    'Bean-to-cup machine': 'Bean-to-Cup',
    'Other': 'Other'
}

# Split the 'brew' column into multiple rows for each brew type
df['brew'] = df['brew'].str.split(',')
df_exploded = df.explode('brew')

# Strip whitespace and map the values to standardized keywords
df_exploded['brew'] = df_exploded['brew'].str.strip()
df_exploded['brew'] = df_exploded['brew'].replace(brew_mapping)

# Count the occurrences of each brew type
brew_counts = df_exploded['brew'].value_counts()

# Calculate the percentage of respondents for each brew type
brew_percentages = (brew_counts / len(df)) * 100

# Filter the brew percentages to include only the brew types of interest
brew_types = ['Pour-over', 'Espresso', 'French Press', 'Other', 
              'Mr. Coffee', 'Cold Brew', 'Pod Machine', 
              'Cometeer', 'Instant Coffee', 'Bean-to-Cup']
brew_percentages = brew_percentages[brew_types]

# Plotting the bar chart
plt.figure(figsize=(12, 8))
plt.barh(brew_percentages.index, brew_percentages.values, color='lightblue')
plt.xlabel('Percentage of Respondents (%)')
plt.ylabel('Brewing Method')
plt.title('Pour-over and Espresso Are the Top Two Categories\nBut People Brew Multiple Types')
plt.xlim(0, 100)  # Setting x-axis from 0% to 100%

# Adding the percentage labels on the bars
for index, value in enumerate(brew_percentages.values):
    plt.text(value + 1, index, f'{value:.1f}%', va='center')

plt.show()
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

# Define the brew types
brew_types = [
    'Pour-over', 'Espresso', 'French Press', 'Other', 'Mr. Coffee',
    'Cold Brew', 'Pod Machine', 'Cometeer', 'Instant Coffee', 'Bean-to-Cup'
]

# Matrix of percentage values (example values showing brewing overlap)
brew_matrix = np.array([
    [100, 27, 15, 2, 5, 3, 7, 0.3, 4, 1],     # Pour-over
    [27, 100, 12, 3, 6, 5, 10, 0.4, 6, 2],    # Espresso
    [15, 12, 100, 1, 3, 8, 5, 0.3, 7, 4],     # French Press
    [2, 3, 1, 100, 2, 2, 1, 0.5, 3, 1],       # Other
    [5, 6, 3, 2, 100, 2, 8, 0.4, 9, 5],       # Mr. Coffee
    [3, 5, 8, 2, 2, 100, 7, 0.4, 6, 3],       # Cold Brew
    [7, 10, 5, 1, 8, 7, 100, 0.5, 4, 3],      # Pod Machine
    [0.3, 0.4, 0.3, 0.5, 0.4, 0.4, 0.5, 100, 0.2, 0.1], # Cometeer
    [4, 6, 7, 3, 9, 6, 4, 0.2, 100, 5],       # Instant Coffee
    [1, 2, 4, 1, 5, 3, 3, 0.1, 5, 100]        # Bean-to-Cup
])

# Set values below 0.5% to NaN to represent blank spaces
brew_matrix[brew_matrix < 0.5] = np.nan

# Plotting the heatmap
plt.figure(figsize=(10, 8))
sns.heatmap(brew_matrix, annot=True, fmt='.1f', cmap='Blues', cbar_kws={'label': 'Percentage'}, 
            linewidths=0.5, linecolor='grey', mask=np.isnan(brew_matrix))

# Set the brew types as labels for rows and columns
plt.xticks(ticks=np.arange(len(brew_types)) + 0.5, labels=brew_types, rotation=45, ha='right')
plt.yticks(ticks=np.arange(len(brew_types)) + 0.5, labels=brew_types, rotation=0)

# Set plot title
plt.title('Coffee Brew Correlation Matrix', fontsize=16)

# Adjust layout to fit labels and display the plot
plt.tight_layout()
plt.show()









# List of keywords to search for in the 'brew' column
keywords = ['Pour-over', 'Espresso', 'French Press', 'Other', 'Mr. Coffee', 
            'Cold Brew', 'Pod Machine', 'Cometeer', 'Instant Coffee', 'Bean-to-Cup']

# Initialize a counter to store the counts for each keyword
keyword_count = Counter()

# Iterate through each row in the 'brew' column
for sentence in df['brew'].dropna():
    # Check if the sentence is a list or string
    if isinstance(sentence, list):
        # If it's a list, join it into a single string
        sentence = ' '.join(sentence)
    
    # Ensure the sentence is a string before proceeding
    if isinstance(sentence, str):
        # Check for each keyword in the sentence
        for keyword in keywords:
            if keyword.lower() in sentence.lower():
                keyword_count[keyword] += 1

# Convert the counter to a DataFrame for better readability
keyword_count_df = pd.DataFrame.from_dict(keyword_count, orient='index', columns=['Count']).reset_index()
keyword_count_df.columns = ['Keyword', 'Count']

# Calculate the total number of respondents
total_respondents = df['brew'].dropna().shape[0]

# Calculate the percentage for each keyword
keyword_count_df['Percentage'] = (keyword_count_df['Count'] / total_respondents) * 100

# Sort values by percentage for better visualization
keyword_count_df = keyword_count_df.sort_values(by='Percentage', ascending=True)

# Plotting
plt.figure(figsize=(10, 6))
plt.barh(keyword_count_df['Keyword'], keyword_count_df['Percentage'], color='skyblue')
plt.xlabel('Percentage of Respondents (%)')
plt.ylabel('Brew Type')
plt.title('Percentage of Respondents by Brew Type')
plt.grid(axis='x', linestyle='--', alpha=0.7)

# Display the plot
plt.show()







import pandas as pd
import matplotlib.pyplot as plt

# Load the CSV file
df = pd.read_csv('coffee_survey.csv')

# List of location types to search for
location_types = ['specialty coffee shop', 'local cafe', 'national chain', 'drive thru', 'deli or supermarket', 'other']

# Strip any leading/trailing spaces from column names
df.columns = df.columns.str.strip()

# Ensure the column exists
column_name = 'purchase'
if column_name not in df.columns:
    raise ValueError(f"The column '{column_name}' does not exist in the DataFrame.")

# Initialize a dictionary to count occurrences
location_count = {location: 0 for location in location_types}

# Iterate through each row in the column
for locations in df[column_name].dropna():
    # Ensure locations is a string before proceeding
    if isinstance(locations, str):
        # Convert locations to lowercase and check for each location type
        locations_lower = locations.lower()
        for location in location_types:
            if location.lower() in locations_lower:
                location_count[location] += 1

# Convert the dictionary to a DataFrame for better readability
location_count_df = pd.DataFrame.from_dict(location_count, orient='index', columns=['Count']).reset_index()
location_count_df.columns = ['Location', 'Count']

# Calculate the total number of respondents
total_respondents = df[column_name].dropna().shape[0]

# Calculate the percentage for each location type
location_count_df['Percentage'] = (location_count_df['Count'] / total_respondents) * 100

# Sort values by percentage for better visualization
location_count_df = location_count_df.sort_values(by='Percentage', ascending=True)

# Plotting
plt.figure(figsize=(10, 6))
plt.barh(location_count_df['Location'], location_count_df['Percentage'], color='skyblue')
plt.xlabel('Percentage of Respondents (%)')
plt.ylabel('Location Type')
plt.title('Percentage of Respondents by Coffee Purchase Location')
plt.grid(axis='x', linestyle='--', alpha=0.7)

# Display the plot
plt.show()






import pandas as pd
import matplotlib.pyplot as plt

# Load the dataset
df = pd.read_csv('coffee_survey.csv')

# Define the addition types
addition_types = ['No - just black', 'Milk, Dairy or Creamer', 'Sugar or sweetener', 'Flavor syrup', 'Other']

# Strip any leading/trailing spaces from column names
df.columns = df.columns.str.strip()

# Ensure 'additions' column exists
if 'additions' not in df.columns:
    raise ValueError("The column 'additions' does not exist in the DataFrame.")

# Initialize a dictionary to count occurrences
addition_count = {addition: 0 for addition in addition_types}

# Iterate through each row in the 'additions' column
for additions in df['additions'].dropna():
    # Ensure additions is a string before proceeding
    if isinstance(additions, str):
        # Convert additions to lowercase and check for each addition type
        additions_lower = additions.lower()
        for addition in addition_types:
            if addition.lower() in additions_lower:
                addition_count[addition] += 1

# Convert the dictionary to a DataFrame for better readability
addition_count_df = pd.DataFrame.from_dict(addition_count, orient='index', columns=['Count']).reset_index()
addition_count_df.columns = ['Addition', 'Count']

# Calculate the total number of respondents
total_respondents = df['additions'].dropna().shape[0]

# Calculate the percentage for each addition type
addition_count_df['Percentage'] = (addition_count_df['Count'] / total_respondents) * 100

# Sort values by percentage for better visualization
addition_count_df = addition_count_df.sort_values(by='Percentage', ascending=True)

# Plotting
plt.figure(figsize=(12, 8))
plt.barh(addition_count_df['Addition'], addition_count_df['Percentage'], color='skyblue')
plt.xlabel('Percentage of Respondents (%)')
plt.ylabel('Addition Type')
plt.title('What Do You Add to Coffee?')

# Adding insight text to the plot
plt.text(0.5, -0.2, 'Most people in this group did not add anything to their coffee.', 
         ha='center', va='center', fontsize=12, color='black', style='italic', transform=plt.gca().transAxes)

# Adding percentage labels on the bars
for index, value in enumerate(addition_count_df['Percentage']):
    plt.text(value + 1, index, f'{value:.1f}%', va='center')

plt.grid(axis='x', linestyle='--', alpha=0.7)
plt.tight_layout()
plt.show()




#-------------------#

import pandas as pd
import matplotlib.pyplot as plt

# Load the dataset
df = pd.read_csv('coffee_survey.csv')

# Define the milk types
milk_types = ['whole milk','Half and half', 'oat milk', 'Flavored coffee creamer', 'coffee creamer',
              'almond milk', 'skim milk', 'soy milk', 'other']

# Strip any leading/trailing spaces from column names
df.columns = df.columns.str.strip()

# Ensure 'dairy' column exists
if 'dairy' not in df.columns:
    raise ValueError("The column 'dairy' does not exist in the DataFrame.")

# Initialize a dictionary to count occurrences
milk_count = {milk: 0 for milk in milk_types}

# Iterate through each row in the 'dairy' column
for milk in df['dairy'].dropna():
    # Ensure milk is a string before proceeding
    if isinstance(milk, str):
        # Convert milk to lowercase and check for each milk type
        milk_lower = milk.lower()
        for milk_type in milk_types:
            if milk_type.lower() in milk_lower:
                milk_count[milk_type] += 1

# Convert the dictionary to a DataFrame for better readability
milk_count_df = pd.DataFrame.from_dict(milk_count, orient='index', columns=['Count']).reset_index()
milk_count_df.columns = ['Milk Type', 'Count']

# Calculate the total number of respondents
total_respondents = df['dairy'].dropna().shape[0]

# Calculate the percentage for each milk type
milk_count_df['Percentage'] = (milk_count_df['Count'] / total_respondents) * 100

# Sort values by percentage for better visualization
milk_count_df = milk_count_df.sort_values(by='Percentage', ascending=True)

# Plotting
plt.figure(figsize=(12, 8))
plt.barh(milk_count_df['Milk Type'], milk_count_df['Percentage'], color='lightgreen')
plt.xlabel('Percentage of Respondents (%)')
plt.ylabel('Milk Type')
plt.title('What Milk Do You Add to Your Coffee?')

# Adding insight text to the plot
plt.text(0.5, -0.1, 'For the milk, people mostly added whole milk, but many used oat milk. Many didn’t add any milk.', 
         ha='center', va='center', fontsize=12, color='black', style='italic', transform=plt.gca().transAxes)

# Adding percentage labels on the bars
for index, value in enumerate(milk_count_df['Percentage']):
    plt.text(value + 1, index, f'{value:.1f}%', va='center')

plt.grid(axis='x', linestyle='--', alpha=0.7)
plt.tight_layout()
plt.show()
