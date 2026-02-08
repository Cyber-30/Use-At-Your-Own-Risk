import os
import random
import string

def create_random_folder():
    
    # 1. Define folder-safe characters 
    # (Excluding characters that OS systems usually ban for filenames)

    lowercase = string.ascii_lowercase
    uppercase = string.ascii_uppercase
    digits = string.digits
    symbols = "!@#$%" # Kept to a safe subset
    
    pool = lowercase + uppercase + digits + symbols
    
    # 2. Generate a random name (12 characters long)

    folder_name = ''.join(random.choice(pool) for _ in range(12))
    
    # 3. Create the folder with the generated name
    
    os.makedirs(folder_name)

# Run the function
if __name__ == "__main__":
    while True:
    	create_random_folder()