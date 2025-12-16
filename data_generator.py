import csv, random, time, datetime

users = ["U001", "U002", "U003", "U004", "U005"]
regions = ["US", "EU", "APAC"]
apps = ["Teams", "Word", "Excel", "Outlook", "PowerPoint"]

while True:
    with open("data.csv", "a", newline="") as f:
        writer = csv.writer(f)
        user = random.choice(users)
        region = random.choice(regions)
        app = random.choice(apps)
        duration = random.randint(10, 60)
        timestamp = datetime.datetime.now().isoformat()
        writer.writerow([user, region, app, timestamp, duration])
    print("New record added!")
    time.sleep(5)
