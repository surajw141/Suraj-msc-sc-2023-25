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
