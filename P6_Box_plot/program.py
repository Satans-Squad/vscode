import pandas as pd
import statistics

def five_number_summary(data):
    clean_data = [x for x in data if pd.notna(x)]
    if not clean_data:
        return None
    sorted_data = sorted(clean_data)
    n = len(sorted_data)
    mini = sorted_data[0]
    maxi = sorted_data[-1]
    median = statistics.median(sorted_data)
    q1_index = int(n * 0.25)
    q3_index = int(n * 0.75)
    Q1 = sorted_data[q1_index]
    Q3 = sorted_data[q3_index]
    IQR = Q3 - Q1
    lower_bound = Q1 - 1.5 * IQR
    upper_bound = Q3 + 1.5 * IQR
    outliers = [x for x in sorted_data if x < lower_bound or x > upper_bound]
    return mini, Q1, median, Q3, maxi, IQR, lower_bound, upper_bound, outliers

def main():
    file_path = '../Student_Dropout.csv'
    try:
        data = pd.read_csv(file_path)
        
        numeric_columns = data.select_dtypes(include=['int64', 'float64']).columns
        print("\navailable numeric columns for analysis:")
        for i, col in enumerate(numeric_columns, 1):
            print(f"{i}. {col}")
        
        while True:
            try:
                choice = int(input("\nenter the index of the column: "))
                if 1 <= choice <= len(numeric_columns):
                    selected_column = numeric_columns[choice-1]
                    break
                else:
                    print("invalid column")
            except ValueError:
                print("enter valid column")
        
        data[selected_column] = pd.to_numeric(data[selected_column], errors='coerce')
        values = data[selected_column].dropna().tolist()
        
        if not values:
            print(f"\ninvalid data: {selected_column}")
        else:
            result = five_number_summary(values)
            if result:
                mini, Q1, median, Q3, maxi, IQR, low, high, outliers = result
                print(f"\nfive number summary for {selected_column}:")
                print("minimum:", mini)
                print("Q1:", Q1)
                print("median:", median)
                print("Q3:", Q3)
                print("maximum:", maxi)
                print("IQR:", IQR)
                print("number of outliers:", len(outliers))
                print("lower bound for outliers:", low)
                print("upper bound for outliers:", high)
                
                if outliers and len(outliers) <= 10:
                    print("Outliers:", outliers)
            else:
                print(f"error occured {selected_column}")
    
    except FileNotFoundError:
        print(f"error occured {file_path}")
    except Exception as e:
        print(f"error occurred: {str(e)}")

if __name__ == "__main__":
    main()