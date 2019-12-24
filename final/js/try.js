$(document).ready(function() {

    var source = $('#todo-list-item-template').html();
    var todoTemplate = Handlebars.compile(source);




    // enter editor mode
    $('#todo-list')
        .on('dblclick', '.content', function(e) {
            $(this).prop('contenteditable', true).focus();
        })
        .on('blur', '.content', function(e) {
            var isNew = $(this).closest('li').is('.new');
            // create
            if (isNew) {
                var todo = $(e.currentTarget).text();
                // eliminate blank
                todo = todo.trim();

                if (todo.length > 0) {
                    todo = {
                        is_complete: false,
                        content: todo,
                    };
                    var li = todoTemplate(todo);
                    $(e.currentTarget).closest('li').before(li);
                }

                $(e.currentTarget).empty();
            }
            // update
            else {
                $(this).prop('contenteditable', false);
            }
        })
        // delete
        .on('click', '.delete', function(e) {
            var result = confirm('Do you want to delete?')
            if (result) {
                $(this).closest('li').remove();
            }
        })
        .on('click', '.checkbox', function(e) {
            if ($(this).closest('li').is('.new')) {

            } else {
                $(this).closest('li').toggleClass('complete');
            }
        });

    // sort
    $('#todo-list').find('ul').sortable({
        items: 'li:not(.new)'
    });
});