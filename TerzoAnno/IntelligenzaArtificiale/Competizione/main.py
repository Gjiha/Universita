import pandas as pd
import emoji as em

pd.set_option("display.max_columns", None)
pd.set_option("max_colwidth", None)

def read__csv(file_path:str):
    dataframe = pd.read_csv(file_path, encoding="utf-8")
    
    return dataframe

def clear_sentence(sentence:str) -> str:
    sentence = sentence.encode('cp1252').decode('utf8')
    return sentence

if __name__ == "__main__":
    df = read__csv("./Dataset/train.csv")

    i = 0

    id = df['ID'].tolist()
    text = df['Text'].tolist()
    label = df['Label'].tolist()
    while i < 10:
        text[i] = clear_sentence(text[i])
        print(f"{id[i]}\t{text[i]}\t{label[i]}")
        print(50*'*')
        i += 1

