# Report on Time Series Analysis of Biodiversity Data
## Objective
The dataset is analyzed to identify trends, seasonality, and stationarity in the time series data, focusing on the individualCount variable over time.

## Data Overview
### 1. Dataset Size: 100,000 rows.
### 2. Key Columns Used:
             
**eventDate** : Representing the timestamp of the event (converted to datetime).
**individualCount** : The count of individuals in each event (cleaned and imputed for analysis).


## Data Cleaning
### 1. Missing Values:

**phylum**: 13 missing values.
**class**: 1,303 missing values.
**order**: 2,956 missing values.
**stateProvince**: 510 missing values.
**individualCount**: Entire column missing (imputed with median value).

### 2. Duplicates: No duplicates found in the dataset.

### 3. Outliers:

- Using the IQR method, no significant outliers were detected in the individualCount.
### 4. Data Type Adjustments:

- eventDate was converted to datetime.
- individualCount was coerced to numeric and missing values were imputed using the column's median.
## Exploratory Analysis
### 1. Initial Visualization:

- A time series plot showed individualCount over time, providing an initial sense of trends.
### 2. Descriptive Statistics:

- individualCount initially had no valid data, and imputation was performed to proceed with the analysis.
## Time Series Decomposition
Using **additive decomposition**:

- **Trend**: Identified a smooth, long-term component indicating gradual changes in individualCount.
- **Seasonality**: Detected periodic fluctuations, likely representing repeating patterns.
- **Residuals**: Residual noise with no obvious structure.
## Stationarity Analysis
### 1. ADF Test Results (Before Log Transformation):

- ADF Statistic: not stationary (failed test).
- p-value: Significantly higher than 0.05.
### 2. Log Transformation and Differencing:

- After applying a log transformation to individualCount, the stationarity improved.
### 3. ADF Test Results (After Log Transformation):

- ADF Statistic: Stationary.
- p-value: Below 0.05, indicating the data is now stationary.


## Autocorrelation and Partial Autocorrelation
**ACF Plot**:

- Significant lags indicate some correlation with past values.

**PACF Plot**:
- Highlighted short-term dependencies, guiding ARIMA modeling.


## ARIMA Modeling


### 1. Model: ARIMA(1,1,1).
### 2. Model Summary:
- Parameters were fitted, showing good model performance.
- Residual analysis indicated minimal autocorrelation, confirming model adequacy.
## Residual Analysis
**Plotted residuals show**:
- Random noise.
- No discernible pattern, confirming the model captures most of the structure.
## Challenges and Notes
- The original individualCount column contained no valid values and required imputation.
- Many other columns (e.g., verbatimScientificNameAuthorship, elevation) contained entirely missing data and were excluded from the analysis.
- A warning regarding chained assignments may need revisiting in future versions of pandas.


## Conclusion
1. The individualCount variable exhibits clear seasonality and trends.
2. Log transformation and differencing effectively stabilized the series for stationarity.
3. The ARIMA(1,1,1) model captured the dynamics of the time series well.
## Recommendations
- Further refine the ARIMA model using SARIMA for capturing seasonality more explicitly.
- Investigate missing data in other columns for potential inclusion in multivariate models.
- Explore additional transformations and feature engineering for deeper insights.