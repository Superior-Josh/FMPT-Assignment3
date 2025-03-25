import os
import struct
from Crypto.Cipher import AES

'''
Change the following line to YOUR directory of the files to be decrypted
DO NOT add a '/' to the end of your directory
'''
FILE_DIRECTORY = "/mnt/d/Cyber-Security/LM Forensics, Malware, and Penetration Testing/assignment3/HanksBackup"

KEY = "8d02e65e508308dd743f0dd4d31e484d"  # AES-128 key

"""
Decrypt a fixed-size ciphertext block and truncate it to the actual plaintext length.
"""
def decrypt_block(ciphertext_block, key, iv, actual_plaintext_len):
    cipher = AES.new(key, AES.MODE_CBC, iv)
    decrypted_block = cipher.decrypt(ciphertext_block)
    # Only keep the actual plaintext length portion, the rest is meaningless padding used during encryption
    return decrypted_block[:actual_plaintext_len]

"""
Decrypt a single file, following the format with fixed-size blocks (1008 bytes):
[16-byte IV][4-byte actual plaintext length][1008-byte ciphertext block]... repeated until the end of the file.
"""
def decrypt_file(input_path, output_path, key_hex):
    key = bytes.fromhex(key_hex)
    BLOCK_SIZE = 0x3F0  # 1008 bytes
    with open(input_path, 'rb') as f_in, open(output_path, 'wb') as f_out:
        while True:
            # Read the 16-byte IV
            iv = f_in.read(16)  #0a0b0c0d0e0fa0b0c0d0e0f0aabbccdd
            if len(iv) < 16:
                break  # End of file
            # Read the 4-byte actual plaintext length
            block_len_bytes = f_in.read(4)
            if len(block_len_bytes) < 4:
                break
            actual_plaintext_len = struct.unpack('<I', block_len_bytes)[0]
            # Read the encrypted 1008-byte block
            ciphertext_block = f_in.read(BLOCK_SIZE)
            if len(ciphertext_block) != BLOCK_SIZE:
                raise ValueError("Ciphertext block is too short")
            plaintext_block = decrypt_block(ciphertext_block, key, iv, actual_plaintext_len)
            f_out.write(plaintext_block)
    print(f"Decryption successed: {output_path}")

def main():
    input_dir = FILE_DIRECTORY 
    output_dir = f"{os.path.splitext(input_dir)[0]}_decrypted"

    os.makedirs(output_dir, exist_ok=True)

    for root, _, files in os.walk(input_dir):
        relative_path = os.path.relpath(root, input_dir)
        if relative_path == '.':
            relative_path = ''
        dest_dir = os.path.join(output_dir, relative_path)
        
        for file in files:
            src_file = os.path.join(root, file)
            dest_file = os.path.join(dest_dir, file)

            os.makedirs(dest_dir, exist_ok=True)

            try:
                decrypt_file(src_file, dest_file, KEY)
            except Exception as e:
                print(f"Decryption failed: {src_file} - {e}")

if __name__ == '__main__':
    main()
