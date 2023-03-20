import random
from faker import Faker
fake = Faker(locale="ru_RU")

def generate_person():
    gender = random.choice(['М', 'Ж'])
    name = fake.name_male() if gender == 'М' else fake.name_female()
    age = random.randint(18, 70)
    workplace = fake.company()
    income = random.randint(20, 500) * 1000
    purpose = random.choice(['Кредит', 'Вклад'])
    return [name, gender, age, workplace, income, purpose]

print('\n'.join([' | '.join(map(str, generate_person())) for _ in range(50)]))
