char *change_pipes(char *text)
{
    /*Changes all single pipes '|' for '#' in a string, but ignores double pipes '||'

    Args:
        text: The string to modify (will be modified in-place).

    Returns:
        The modified string (same pointer as input).
    */
    char *result = text;
    char *p = text;

    while (*p)
    {
        if (*p == '|' && *(p + 1) != '|' && *(p-1) != '|')
        {
            *p = '#';
        }
        *result++ = *p++;
    }

    *result = '\0'; // Ensure null termination after modification
    return text;
}