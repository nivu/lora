import mysql.connector

mydb = mysql.connector.connect(
    host="localhost",
    user="root",
    passwd="",
    database="lora"
)

mycursor = mydb.cursor()

sql = "INSERT INTO test (node_id) VALUES (1)"
mycursor.execute(sql)

mydb.commit()

print(mycursor.rowcount, "record inserted.")
