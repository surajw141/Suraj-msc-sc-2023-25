import pandas as pd
import matplotlib.pyplot as plt

# Load the dataset into a Pandas DataFrame
df = pd.read_csv('olympics.csv')

# 1. How many total countries are listed in the table?
country_count = df['noc'].nunique()
print(f"Total countries listed: {country_count}")

# 2. How many gold, silver, and bronze medals has India won?
india_medals = df[df['team'] == 'India'].groupby('medal').size()
gold = india_medals.get('Gold', 0)
silver = india_medals.get('Silver', 0)
bronze = india_medals.get('Bronze', 0)
total = gold + silver + bronze
print(f"India - Gold: {gold}, Silver: {silver}, Bronze: {bronze}, Total: {total}")

# 3. Plot a boxplot of ages of all athletes
plt.figure(figsize=(10, 6))
plt.boxplot(df['age'].dropna(), vert=False)
plt.title('Boxplot of Ages of All Athletes')
plt.xlabel('Age')
plt.show()

# 4. Plot a boxplot of ages of Indian athletes
plt.figure(figsize=(10, 6))
plt.boxplot(df[df['team'] == 'India']['age'].dropna(), vert=False)
plt.title('Boxplot of Ages of Indian Athletes')
plt.xlabel('Age')
plt.show()

# 5. Median and mean ages of male and female athletes
median_age = df.groupby('sex')['age'].median()
mean_age = df.groupby('sex')['age'].mean()
print(f"Median Age - Male: {median_age['M']}, Female: {median_age['F']}")
print(f"Mean Age - Male: {mean_age['M']}, Female: {mean_age['F']}")

# 6. Plot the ratio of male to female athletes for each Olympic
gender_count = df.groupby(['year', 'sex']).size().unstack(fill_value=0)
gender_ratio = gender_count['M'] / gender_count['F']

plt.figure(figsize=(10, 6))
plt.plot(gender_ratio.index, gender_ratio.values, marker='o')
plt.title('Male to Female Athlete Ratio Over the Years')
plt.xlabel('Year')
plt.ylabel('Male to Female Ratio')
plt.grid(True)
plt.show()

