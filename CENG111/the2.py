my_dict = eval(input()) 
income = eval(input())  
final_tax_amount=0
if my_dict['INCOME'] == 'low':
    final_tax_amount = income*0.1
elif my_dict['INCOME'] == 'middle':
    final_tax_amount = income*0.2
elif my_dict['INCOME'] == 'high':
    final_tax_amount = income*0.3
number_of_child = len(my_dict['CHILD'])
if my_dict['MARITAL_STATUS'] == 'single':
    final_tax_amount = final_tax_amount
elif my_dict['MARITAL_STATUS'] == 'married':
    final_tax_amount -= 500 + number_of_child*300
elif my_dict['MARITAL_STATUS'] == 'single_parent':
    final_tax_amount -= number_of_child*600
child_under_18 = len(list(filter(lambda age: age < 18, my_dict['CHILD'])))
final_tax_amount -= child_under_18*200
if my_dict['SPECIAL_NEEDS']==True: 
    final_tax_amount -= 1000
if my_dict['ELDERLY_CARE']==True:  
    final_tax_amount -= 800
if my_dict['CITY_CATEGORY']=='urban':
    final_tax_amount=final_tax_amount
elif my_dict['CITY_CATEGORY'] == 'suburban':
    final_tax_amount -= 200
elif my_dict['CITY_CATEGORY'] == 'rural':
    final_tax_amount -= 400
if my_dict['EDUCATION']==True:
    final_tax_amount -= 500
if my_dict['HEALTHCARE']==True:
    final_tax_amount -= 750
if my_dict['GREEN_INITIATIVES']==True:
    final_tax_amount -= 300
if my_dict['PROPERTY_STATUS'] == 'owns':
    final_tax_amount=final_tax_amount
elif my_dict['PROPERTY_STATUS'] == 'rents':
    final_tax_amount -= 300
if my_dict['TAXPAYER_DURATION'] == 'regular':
    final_tax_amount -= final_tax_amount*0.05
elif my_dict['TAXPAYER_DURATION'] == 'long_term':
    final_tax_amount -= final_tax_amount*0.10
if final_tax_amount<0:
   final_tax_amount=0      
print("%.2f" % final_tax_amount)
